/*
 *  Copyright 2008-2013 NVIDIA Corporation
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

#include <hydra/detail/external/thrust/detail/config.h>
#include <hydra/detail/external/thrust/system/detail/sequential/copy.h>
#include <hydra/detail/external/thrust/detail/type_traits.h>
#include <hydra/detail/external/thrust/system/detail/sequential/general_copy.h>
#include <hydra/detail/external/thrust/system/detail/sequential/trivial_copy.h>
#include <hydra/detail/external/thrust/iterator/iterator_traits.h>
#include <hydra/detail/external/thrust/detail/type_traits/pointer_traits.h>
#include <hydra/detail/external/thrust/type_traits/is_trivially_relocatable.h>

HYDRA_EXTERNAL_NAMESPACE_BEGIN  namespace thrust
{
namespace system
{
namespace detail
{
namespace sequential
{
namespace copy_detail
{


// returns the raw pointer associated with a Pointer-like thing
template<typename Pointer>
__hydra_host__ __hydra_device__
  typename HYDRA_EXTERNAL_NS::thrust::detail::pointer_traits<Pointer>::raw_pointer
    get(Pointer ptr)
{
  return HYDRA_EXTERNAL_NS::thrust::detail::pointer_traits<Pointer>::get(ptr);
}


__thrust_exec_check_disable__
template<typename InputIterator,
         typename OutputIterator>
__hydra_host__ __hydra_device__
  OutputIterator copy(InputIterator first,
                      InputIterator last,
                      OutputIterator result,
                      HYDRA_EXTERNAL_NS::thrust::detail::true_type)  // is_indirectly_trivially_relocatable_to
{
  typedef typename HYDRA_EXTERNAL_NS::thrust::iterator_difference<InputIterator>::type Size;

  const Size n = last - first;
  HYDRA_EXTERNAL_NS::thrust::system::detail::sequential::trivial_copy_n(get(&*first), n, get(&*result));
  return result + n;
} // end copy()


__thrust_exec_check_disable__
template<typename InputIterator,
         typename OutputIterator>
__hydra_host__ __hydra_device__
  OutputIterator copy(InputIterator first,
                      InputIterator last,
                      OutputIterator result,
                      HYDRA_EXTERNAL_NS::thrust::detail::false_type)  // is_indirectly_trivially_relocatable_to
{
  return HYDRA_EXTERNAL_NS::thrust::system::detail::sequential::general_copy(first,last,result);
} // end copy()


__thrust_exec_check_disable__
template<typename InputIterator,
         typename Size,
         typename OutputIterator>
__hydra_host__ __hydra_device__
  OutputIterator copy_n(InputIterator first,
                        Size n,
                        OutputIterator result,
                        HYDRA_EXTERNAL_NS::thrust::detail::true_type)  // is_indirectly_trivially_relocatable_to
{
  HYDRA_EXTERNAL_NS::thrust::system::detail::sequential::trivial_copy_n(get(&*first), n, get(&*result));
  return result + n;
} // end copy_n()


__thrust_exec_check_disable__
template<typename InputIterator,
         typename Size,
         typename OutputIterator>
__hydra_host__ __hydra_device__
  OutputIterator copy_n(InputIterator first,
                        Size n,
                        OutputIterator result,
                        HYDRA_EXTERNAL_NS::thrust::detail::false_type)  // is_indirectly_trivially_relocatable_to
{
  return HYDRA_EXTERNAL_NS::thrust::system::detail::sequential::general_copy_n(first,n,result);
} // end copy_n()


} // end namespace copy_detail


__thrust_exec_check_disable__
template<typename DerivedPolicy,
         typename InputIterator,
         typename OutputIterator>
__hydra_host__ __hydra_device__
  OutputIterator copy(sequential::execution_policy<DerivedPolicy> &,
                      InputIterator first,
                      InputIterator last,
                      OutputIterator result)
{
  return HYDRA_EXTERNAL_NS::thrust::system::detail::sequential::copy_detail::copy(first, last, result,
    typename HYDRA_EXTERNAL_NS::thrust::is_indirectly_trivially_relocatable_to<InputIterator,OutputIterator>::type());
} // end copy()


__thrust_exec_check_disable__
template<typename DerivedPolicy,
         typename InputIterator,
         typename Size,
         typename OutputIterator>
__hydra_host__ __hydra_device__
  OutputIterator copy_n(sequential::execution_policy<DerivedPolicy> &,
                        InputIterator first,
                        Size n,
                        OutputIterator result)
{
  return HYDRA_EXTERNAL_NS::thrust::system::detail::sequential::copy_detail::copy_n(first, n, result,
    typename HYDRA_EXTERNAL_NS::thrust::is_indirectly_trivially_relocatable_to<InputIterator,OutputIterator>::type());
} // end copy_n()


} // end namespace sequential
} // end namespace detail
} // end namespace system
} // end HYDRA_EXTERNAL_NAMESPACE_BEGIN  namespace thrust
HYDRA_EXTERNAL_NAMESPACE_END
