/*
 *  Copyright 2008-2018 NVIDIA Corporation
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#pragma once

#include <hydra/detail/external/thrust/detail/config.h>
#include <hydra/detail/external/thrust/iterator/iterator_adaptor.h>
#include <hydra/detail/external/thrust/iterator/detail/iterator_traversal_tags.h>
#include <hydra/detail/external/thrust/detail/type_traits/pointer_traits.h>
#include <hydra/detail/external/thrust/detail/type_traits.h>
#include <hydra/detail/external/thrust/detail/reference_forward_declaration.h>
#include <ostream>


HYDRA_EXTERNAL_NAMESPACE_BEGIN  namespace thrust
{

// declare pointer with default values of template parameters
template<typename Element, typename Tag, typename Reference = use_default, typename Derived = use_default> class pointer;

} // end HYDRA_EXTERNAL_NAMESPACE_BEGIN  namespace thrust


HYDRA_EXTERNAL_NAMESPACE_END

// specialize HYDRA_EXTERNAL_NS::thrust::iterator_traits to avoid problems with the name of
// pointer's constructor shadowing its nested pointer type
// do this before pointer is defined so the specialization is correctly
// used inside the definition
HYDRA_EXTERNAL_NAMESPACE_BEGIN  namespace thrust
{

template<typename Element, typename Tag, typename Reference, typename Derived>
  struct iterator_traits<HYDRA_EXTERNAL_NS::thrust::pointer<Element,Tag,Reference,Derived> >
{
  private:
    typedef HYDRA_EXTERNAL_NS::thrust::pointer<Element,Tag,Reference,Derived> ptr;

  public:
    typedef typename ptr::iterator_category iterator_category;
    typedef typename ptr::value_type        value_type;
    typedef typename ptr::difference_type   difference_type;
    // XXX implement this type (the result of operator->) later
    typedef void                             pointer;
    typedef typename ptr::reference         reference;
}; // end iterator_traits

} // end HYDRA_EXTERNAL_NAMESPACE_BEGIN  namespace thrust

HYDRA_EXTERNAL_NAMESPACE_END

HYDRA_EXTERNAL_NAMESPACE_BEGIN  namespace thrust
{

namespace detail
{

// this metafunction computes the type of iterator_adaptor HYDRA_EXTERNAL_NS::thrust::pointer should inherit from
template<typename Element, typename Tag, typename Reference, typename Derived>
  struct pointer_base
{
  // void pointers should have no element type
  // note that we remove_cv from the Element type to get the value_type
  typedef typename HYDRA_EXTERNAL_NS::thrust::detail::eval_if<
    HYDRA_EXTERNAL_NS::thrust::detail::is_void<typename HYDRA_EXTERNAL_NS::thrust::detail::remove_const<Element>::type>::value,
    HYDRA_EXTERNAL_NS::thrust::detail::identity_<void>,
    HYDRA_EXTERNAL_NS::thrust::detail::remove_cv<Element>
  >::type value_type;

  // if no Derived type is given, just use pointer
  typedef typename HYDRA_EXTERNAL_NS::thrust::detail::eval_if<
    HYDRA_EXTERNAL_NS::thrust::detail::is_same<Derived,use_default>::value,
    HYDRA_EXTERNAL_NS::thrust::detail::identity_<pointer<Element,Tag,Reference,Derived> >,
    HYDRA_EXTERNAL_NS::thrust::detail::identity_<Derived>
  >::type derived_type;

  // void pointers should have no reference type
  // if no Reference type is given, just use reference
  typedef typename HYDRA_EXTERNAL_NS::thrust::detail::eval_if<
    HYDRA_EXTERNAL_NS::thrust::detail::is_void<typename HYDRA_EXTERNAL_NS::thrust::detail::remove_const<Element>::type>::value,
    HYDRA_EXTERNAL_NS::thrust::detail::identity_<void>,
    HYDRA_EXTERNAL_NS::thrust::detail::eval_if<
      HYDRA_EXTERNAL_NS::thrust::detail::is_same<Reference,use_default>::value,
      HYDRA_EXTERNAL_NS::thrust::detail::identity_<reference<Element,derived_type> >,
      HYDRA_EXTERNAL_NS::thrust::detail::identity_<Reference>
    >
  >::type reference_arg;

  typedef HYDRA_EXTERNAL_NS::thrust::iterator_adaptor<
    derived_type,                        // pass along the type of our Derived class to iterator_adaptor
    Element *,                           // we adapt a raw pointer
    value_type,                          // the value type
    Tag,                                 // system tag
    HYDRA_EXTERNAL_NS::thrust::random_access_traversal_tag, // pointers have random access traversal
    reference_arg,                       // pass along our Reference type
    std::ptrdiff_t
  > type;
}; // end pointer_base


} // end detail


// the base type for all of thrust's tagged pointers.
// for reasonable pointer-like semantics, derived types should reimplement the following:
// 1. no-argument constructor
// 2. constructor from OtherElement *
// 3. constructor from OtherPointer related by convertibility
// 4. constructor from OtherPointer to void
// 5. assignment from OtherPointer related by convertibility
// These should just call the corresponding members of pointer.
template<typename Element, typename Tag, typename Reference, typename Derived>
  class pointer
    : public HYDRA_EXTERNAL_NS::thrust::detail::pointer_base<Element,Tag,Reference,Derived>::type
{
  private:
    typedef typename HYDRA_EXTERNAL_NS::thrust::detail::pointer_base<Element,Tag,Reference,Derived>::type         super_t;

    typedef typename HYDRA_EXTERNAL_NS::thrust::detail::pointer_base<Element,Tag,Reference,Derived>::derived_type derived_type;

    // friend iterator_core_access to give it access to dereference
    friend class HYDRA_EXTERNAL_NS::thrust::iterator_core_access;

    __hydra_host__ __hydra_device__
    typename super_t::reference dereference() const;

    // don't provide access to this part of super_t's interface
    using super_t::base;
    using typename super_t::base_type;

  public:
    typedef typename super_t::base_type raw_pointer;

    // constructors

    __hydra_host__ __hydra_device__
    pointer();

    #if HYDRA_THRUST_CPP_DIALECT >= 2011
    // NOTE: This is needed so that Thrust smart pointers can be used in
    // `std::unique_ptr`.
    __hydra_host__ __hydra_device__
    pointer(decltype(nullptr));
    #endif

    // OtherValue shall be convertible to Value
    // XXX consider making the pointer implementation a template parameter which defaults to Element *
    template<typename OtherElement>
    __hydra_host__ __hydra_device__
    explicit pointer(OtherElement *ptr);

    // OtherPointer's element_type shall be convertible to Element
    // OtherPointer's system shall be convertible to Tag
    template<typename OtherPointer>
    __hydra_host__ __hydra_device__
    pointer(const OtherPointer &other,
            typename HYDRA_EXTERNAL_NS::thrust::detail::enable_if_pointer_is_convertible<
              OtherPointer,
              pointer<Element,Tag,Reference,Derived>
            >::type * = 0);

    // OtherPointer's element_type shall be void
    // OtherPointer's system shall be convertible to Tag
    template<typename OtherPointer>
    __hydra_host__ __hydra_device__
    explicit
    pointer(const OtherPointer &other,
            typename HYDRA_EXTERNAL_NS::thrust::detail::enable_if_void_pointer_is_system_convertible<
              OtherPointer,
              pointer<Element,Tag,Reference,Derived>
            >::type * = 0);

    // assignment

    #if HYDRA_THRUST_CPP_DIALECT >= 2011
    // NOTE: This is needed so that Thrust smart pointers can be used in
    // `std::unique_ptr`.
    __hydra_host__ __hydra_device__
    derived_type& operator=(decltype(nullptr));
    #endif

    // OtherPointer's element_type shall be convertible to Element
    // OtherPointer's system shall be convertible to Tag
    template<typename OtherPointer>
    __hydra_host__ __hydra_device__
    typename HYDRA_EXTERNAL_NS::thrust::detail::enable_if_pointer_is_convertible<
      OtherPointer,
      pointer,
      derived_type &
    >::type
    operator=(const OtherPointer &other);

    // observers

    __hydra_host__ __hydra_device__
    Element *get() const;

    #if HYDRA_THRUST_CPP_DIALECT >= 2011
    // NOTE: This is needed so that Thrust smart pointers can be used in
    // `std::unique_ptr`.
    __hydra_host__ __hydra_device__
    explicit operator bool() const;
    #endif
}; // end pointer

// Output stream operator
template<typename Element, typename Tag, typename Reference, typename Derived,
         typename charT, typename traits>
__hydra_host__
std::basic_ostream<charT, traits> &
operator<<(std::basic_ostream<charT, traits> &os,
           const pointer<Element, Tag, Reference, Derived> &p);

#if HYDRA_THRUST_CPP_DIALECT >= 2011
// NOTE: This is needed so that Thrust smart pointers can be used in
// `std::unique_ptr`.
template <typename Element, typename Tag, typename Reference, typename Derived>
__hydra_host__ __hydra_device__
bool operator==(decltype(nullptr), pointer<Element, Tag, Reference, Derived> p);

template <typename Element, typename Tag, typename Reference, typename Derived>
__hydra_host__ __hydra_device__
bool operator==(pointer<Element, Tag, Reference, Derived> p, decltype(nullptr));

template <typename Element, typename Tag, typename Reference, typename Derived>
__hydra_host__ __hydra_device__
bool operator!=(decltype(nullptr), pointer<Element, Tag, Reference, Derived> p);

template <typename Element, typename Tag, typename Reference, typename Derived>
__hydra_host__ __hydra_device__
bool operator!=(pointer<Element, Tag, Reference, Derived> p, decltype(nullptr));
#endif

} // end HYDRA_EXTERNAL_NAMESPACE_BEGIN  namespace thrust

HYDRA_EXTERNAL_NAMESPACE_END

#include <hydra/detail/external/thrust/detail/pointer.inl>

