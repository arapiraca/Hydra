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


/*! \file uninitialized_fill.h
 *  \brief Copy construction into a range of uninitialized elements from a source value
 */

#pragma once

#include <hydra/detail/external/thrust/detail/config.h>
#include <hydra/detail/external/thrust/detail/execution_policy.h>

HYDRA_EXTERNAL_NAMESPACE_BEGIN  namespace thrust
{


/*! \addtogroup filling
 *  \ingroup transformations
 *  \{
 */


/*! In \c thrust, the function \c HYDRA_EXTERNAL_NS::thrust::device_new allocates memory for
 *  an object and then creates an object at that location by calling a
 *  constructor. Occasionally, however, it is useful to separate those two
 *  operations. If each iterator in the range <tt>[first, last)</tt> points
 *  to uninitialized memory, then \p uninitialized_fill creates copies of \c x
 *  in that range. That is, for each iterator \c i in the range <tt>[first, last)</tt>,
 *  \p uninitialized_fill creates a copy of \c x in the location pointed to \c i by
 *  calling \p ForwardIterator's \c value_type's copy constructor.
 *
 *  The algorithm's execution is parallelized as determined by \p exec.
 *  
 *  \param exec The execution policy to use for parallelization.
 *  \param first The first element of the range of interest.
 *  \param last The last element of the range of interest.
 *  \param x The value to use as the exemplar of the copy constructor.
 *
 *  \tparam DerivedPolicy The name of the derived execution policy.
 *  \tparam ForwardIterator is a model of <a href="http://www.sgi.com/tech/stl/ForwardIterator">Forward Iterator</a>,
 *          \p ForwardIterator is mutable, and \p ForwardIterator's \c value_type has a constructor that
 *          takes a single argument of type \p T.
 *
 *  The following code snippet demonstrates how to use \p uninitialized_fill to initialize a range of
 *  uninitialized memory using the \p HYDRA_EXTERNAL_NS::thrust::device execution policy for parallelization:
 *
 *  \code
 *  #include <hydra/detail/external/thrust/uninitialized_fill.h>
 *  #include <hydra/detail/external/thrust/device_malloc.h>
 *  #include <hydra/detail/external/thrust/execution_policy.h>
 *  
 *  struct Int
 *  {
 *    __hydra_host__ __hydra_device__
 *    Int(int x) : val(x) {}
 *    int val;
 *  };  
 *  ...
 *  const int N = 137;
 *
 *  Int val(46);
 *  HYDRA_EXTERNAL_NS::thrust::device_ptr<Int> array = HYDRA_EXTERNAL_NS::thrust::device_malloc<Int>(N);
 *  HYDRA_EXTERNAL_NS::thrust::uninitialized_fill(HYDRA_EXTERNAL_NS::thrust::device, array, array + N, val);
 *
 *  // Int x = array[i];
 *  // x.val == 46 for all 0 <= i < N
 *  \endcode
 *
 *  \see http://www.sgi.com/tech/stl/uninitialized_fill.html
 *  \see \c uninitialized_fill_n
 *  \see \c fill
 *  \see \c uninitialized_copy
 *  \see \c device_new
 *  \see \c device_malloc
 */
template<typename DerivedPolicy, typename ForwardIterator, typename T>
__hydra_host__ __hydra_device__
  void uninitialized_fill(const HYDRA_EXTERNAL_NS::thrust::detail::execution_policy_base<DerivedPolicy> &exec,
                          ForwardIterator first,
                          ForwardIterator last,
                          const T &x);


/*! In \c thrust, the function \c HYDRA_EXTERNAL_NS::thrust::device_new allocates memory for
 *  an object and then creates an object at that location by calling a
 *  constructor. Occasionally, however, it is useful to separate those two
 *  operations. If each iterator in the range <tt>[first, last)</tt> points
 *  to uninitialized memory, then \p uninitialized_fill creates copies of \c x
 *  in that range. That is, for each iterator \c i in the range <tt>[first, last)</tt>,
 *  \p uninitialized_fill creates a copy of \c x in the location pointed to \c i by
 *  calling \p ForwardIterator's \c value_type's copy constructor.
 *  
 *  \param first The first element of the range of interest.
 *  \param last The last element of the range of interest.
 *  \param x The value to use as the exemplar of the copy constructor.
 *
 *  \tparam ForwardIterator is a model of <a href="http://www.sgi.com/tech/stl/ForwardIterator">Forward Iterator</a>,
 *          \p ForwardIterator is mutable, and \p ForwardIterator's \c value_type has a constructor that
 *          takes a single argument of type \p T.
 *
 *  The following code snippet demonstrates how to use \p uninitialized_fill to initialize a range of
 *  uninitialized memory.
 *
 *  \code
 *  #include <hydra/detail/external/thrust/uninitialized_fill.h>
 *  #include <hydra/detail/external/thrust/device_malloc.h>
 *  
 *  struct Int
 *  {
 *    __hydra_host__ __hydra_device__
 *    Int(int x) : val(x) {}
 *    int val;
 *  };  
 *  ...
 *  const int N = 137;
 *
 *  Int val(46);
 *  HYDRA_EXTERNAL_NS::thrust::device_ptr<Int> array = HYDRA_EXTERNAL_NS::thrust::device_malloc<Int>(N);
 *  HYDRA_EXTERNAL_NS::thrust::uninitialized_fill(array, array + N, val);
 *
 *  // Int x = array[i];
 *  // x.val == 46 for all 0 <= i < N
 *  \endcode
 *
 *  \see http://www.sgi.com/tech/stl/uninitialized_fill.html
 *  \see \c uninitialized_fill_n
 *  \see \c fill
 *  \see \c uninitialized_copy
 *  \see \c device_new
 *  \see \c device_malloc
 */
template<typename ForwardIterator, typename T>
  void uninitialized_fill(ForwardIterator first,
                          ForwardIterator last,
                          const T &x);


/*! In \c thrust, the function \c HYDRA_EXTERNAL_NS::thrust::device_new allocates memory for
 *  an object and then creates an object at that location by calling a
 *  constructor. Occasionally, however, it is useful to separate those two
 *  operations. If each iterator in the range <tt>[first, first+n)</tt> points
 *  to uninitialized memory, then \p uninitialized_fill creates copies of \c x
 *  in that range. That is, for each iterator \c i in the range <tt>[first, first+n)</tt>,
 *  \p uninitialized_fill creates a copy of \c x in the location pointed to \c i by
 *  calling \p ForwardIterator's \c value_type's copy constructor.
 *
 *  The algorithm's execution is parallelized as determined by \p exec.
 *  
 *  \param exec The execution policy to use for parallelization.
 *  \param first The first element of the range of interest.
 *  \param n The size of the range of interest.
 *  \param x The value to use as the exemplar of the copy constructor.
 *  \return <tt>first+n</tt>
 *
 *  \tparam DerivedPolicy The name of the derived execution policy.
 *  \tparam ForwardIterator is a model of <a href="http://www.sgi.com/tech/stl/ForwardIterator">Forward Iterator</a>,
 *          \p ForwardIterator is mutable, and \p ForwardIterator's \c value_type has a constructor that
 *          takes a single argument of type \p T.
 *
 *  The following code snippet demonstrates how to use \p uninitialized_fill to initialize a range of
 *  uninitialized memory using the \p HYDRA_EXTERNAL_NS::thrust::device execution policy for parallelization:
 *
 *  \code
 *  #include <hydra/detail/external/thrust/uninitialized_fill.h>
 *  #include <hydra/detail/external/thrust/device_malloc.h>
 *  #include <hydra/detail/external/thrust/execution_policy.h>
 *  
 *  struct Int
 *  {
 *    __hydra_host__ __hydra_device__
 *    Int(int x) : val(x) {}
 *    int val;
 *  };  
 *  ...
 *  const int N = 137;
 *
 *  Int val(46);
 *  HYDRA_EXTERNAL_NS::thrust::device_ptr<Int> array = HYDRA_EXTERNAL_NS::thrust::device_malloc<Int>(N);
 *  HYDRA_EXTERNAL_NS::thrust::uninitialized_fill_n(HYDRA_EXTERNAL_NS::thrust::device, array, N, val);
 *
 *  // Int x = array[i];
 *  // x.val == 46 for all 0 <= i < N
 *  \endcode
 *
 *  \see http://www.sgi.com/tech/stl/uninitialized_fill.html
 *  \see \c uninitialized_fill
 *  \see \c fill
 *  \see \c uninitialized_copy_n
 *  \see \c device_new
 *  \see \c device_malloc
 */
template<typename DerivedPolicy, typename ForwardIterator, typename Size, typename T>
__hydra_host__ __hydra_device__
  ForwardIterator uninitialized_fill_n(const HYDRA_EXTERNAL_NS::thrust::detail::execution_policy_base<DerivedPolicy> &exec,
                                       ForwardIterator first,
                                       Size n,
                                       const T &x);


/*! In \c thrust, the function \c HYDRA_EXTERNAL_NS::thrust::device_new allocates memory for
 *  an object and then creates an object at that location by calling a
 *  constructor. Occasionally, however, it is useful to separate those two
 *  operations. If each iterator in the range <tt>[first, first+n)</tt> points
 *  to uninitialized memory, then \p uninitialized_fill creates copies of \c x
 *  in that range. That is, for each iterator \c i in the range <tt>[first, first+n)</tt>,
 *  \p uninitialized_fill creates a copy of \c x in the location pointed to \c i by
 *  calling \p ForwardIterator's \c value_type's copy constructor.
 *  
 *  \param first The first element of the range of interest.
 *  \param n The size of the range of interest.
 *  \param x The value to use as the exemplar of the copy constructor.
 *  \return <tt>first+n</tt>
 *
 *  \tparam ForwardIterator is a model of <a href="http://www.sgi.com/tech/stl/ForwardIterator">Forward Iterator</a>,
 *          \p ForwardIterator is mutable, and \p ForwardIterator's \c value_type has a constructor that
 *          takes a single argument of type \p T.
 *
 *  The following code snippet demonstrates how to use \p uninitialized_fill to initialize a range of
 *  uninitialized memory.
 *
 *  \code
 *  #include <hydra/detail/external/thrust/uninitialized_fill.h>
 *  #include <hydra/detail/external/thrust/device_malloc.h>
 *  
 *  struct Int
 *  {
 *    __hydra_host__ __hydra_device__
 *    Int(int x) : val(x) {}
 *    int val;
 *  };  
 *  ...
 *  const int N = 137;
 *
 *  Int val(46);
 *  HYDRA_EXTERNAL_NS::thrust::device_ptr<Int> array = HYDRA_EXTERNAL_NS::thrust::device_malloc<Int>(N);
 *  HYDRA_EXTERNAL_NS::thrust::uninitialized_fill_n(array, N, val);
 *
 *  // Int x = array[i];
 *  // x.val == 46 for all 0 <= i < N
 *  \endcode
 *
 *  \see http://www.sgi.com/tech/stl/uninitialized_fill.html
 *  \see \c uninitialized_fill
 *  \see \c fill
 *  \see \c uninitialized_copy_n
 *  \see \c device_new
 *  \see \c device_malloc
 */
template<typename ForwardIterator, typename Size, typename T>
  ForwardIterator uninitialized_fill_n(ForwardIterator first,
                                       Size n,
                                       const T &x);

/*! \} // end filling
 *  \} // transformations
 */

} // end HYDRA_EXTERNAL_NAMESPACE_BEGIN  namespace thrust

HYDRA_EXTERNAL_NAMESPACE_END

#include <hydra/detail/external/thrust/detail/uninitialized_fill.inl>

