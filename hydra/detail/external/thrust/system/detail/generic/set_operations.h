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

#pragma once

#include <hydra/detail/external/thrust/detail/config.h>
#include <hydra/detail/external/thrust/system/detail/generic/tag.h>
#include <hydra/detail/external/thrust/pair.h>

HYDRA_EXTERNAL_NAMESPACE_BEGIN  namespace thrust
{
namespace system
{
namespace detail
{
namespace generic
{


template<typename ExecutionPolicy,
         typename InputIterator1,
         typename InputIterator2,
         typename OutputIterator>
__hydra_host__ __hydra_device__
OutputIterator set_difference(HYDRA_EXTERNAL_NS::thrust::execution_policy<ExecutionPolicy> &exec,
                              InputIterator1                             first1,
                              InputIterator1                             last1,
                              InputIterator2                             first2,
                              InputIterator2                             last2,
                              OutputIterator                             result);


// XXX it is an error to call this function; it has no implementation
template<typename ExecutionPolicy,
         typename InputIterator1,
         typename InputIterator2,
         typename OutputIterator,
         typename StrictWeakOrdering>
__hydra_host__ __hydra_device__
OutputIterator set_difference(HYDRA_EXTERNAL_NS::thrust::execution_policy<ExecutionPolicy> &exec,
                              InputIterator1                             first1,
                              InputIterator1                             last1,
                              InputIterator2                             first2,
                              InputIterator2                             last2,
                              OutputIterator                             result,
                              StrictWeakOrdering                         comp);


template<typename ExecutionPolicy,
         typename InputIterator1,
         typename InputIterator2,
         typename InputIterator3,
         typename InputIterator4,
         typename OutputIterator1,
         typename OutputIterator2>
__hydra_host__ __hydra_device__
HYDRA_EXTERNAL_NS::thrust::pair<OutputIterator1,OutputIterator2>
  set_difference_by_key(HYDRA_EXTERNAL_NS::thrust::execution_policy<ExecutionPolicy> &exec,
                        InputIterator1                             keys_first1,
                        InputIterator1                             keys_last1,
                        InputIterator2                             keys_first2,
                        InputIterator2                             keys_last2,
                        InputIterator3                             values_first1,
                        InputIterator4                             values_first2,
                        OutputIterator1                            keys_result,
                        OutputIterator2                            values_result);


template<typename ExecutionPolicy,
         typename InputIterator1,
         typename InputIterator2,
         typename InputIterator3,
         typename InputIterator4,
         typename OutputIterator1,
         typename OutputIterator2,
         typename StrictWeakOrdering>
__hydra_host__ __hydra_device__
HYDRA_EXTERNAL_NS::thrust::pair<OutputIterator1,OutputIterator2>
  set_difference_by_key(HYDRA_EXTERNAL_NS::thrust::execution_policy<ExecutionPolicy> &exec,
                        InputIterator1                             keys_first1,
                        InputIterator1                             keys_last1,
                        InputIterator2                             keys_first2,
                        InputIterator2                             keys_last2,
                        InputIterator3                             values_first1,
                        InputIterator4                             values_first2,
                        OutputIterator1                            keys_result,
                        OutputIterator2                            values_result,
                        StrictWeakOrdering                         comp);


template<typename ExecutionPolicy,
         typename InputIterator1,
         typename InputIterator2,
         typename OutputIterator>
__hydra_host__ __hydra_device__
OutputIterator set_intersection(HYDRA_EXTERNAL_NS::thrust::execution_policy<ExecutionPolicy> &system,
                                InputIterator1                             first1,
                                InputIterator1                             last1,
                                InputIterator2                             first2,
                                InputIterator2                             last2,
                                OutputIterator                             result);


// XXX it is an error to call this function; it has no implementation
template<typename ExecutionPolicy,
         typename InputIterator1,
         typename InputIterator2,
         typename OutputIterator,
         typename StrictWeakOrdering>
__hydra_host__ __hydra_device__
OutputIterator set_intersection(HYDRA_EXTERNAL_NS::thrust::execution_policy<StrictWeakOrdering> &system,
                                InputIterator1                                first1,
                                InputIterator1                                last1,
                                InputIterator2                                first2,
                                InputIterator2                                last2,
                                OutputIterator                                result,
                                StrictWeakOrdering                            comp);


template<typename ExecutionPolicy,
         typename InputIterator1,
         typename InputIterator2,
         typename InputIterator3,
         typename OutputIterator1,
         typename OutputIterator2>
__hydra_host__ __hydra_device__
HYDRA_EXTERNAL_NS::thrust::pair<OutputIterator1,OutputIterator2>
  set_intersection_by_key(HYDRA_EXTERNAL_NS::thrust::execution_policy<ExecutionPolicy> &system,
                          InputIterator1                             keys_first1,
                          InputIterator1                             keys_last1,
                          InputIterator2                             keys_first2,
                          InputIterator2                             keys_last2,
                          InputIterator3                             values_first1,
                          OutputIterator1                            keys_result,
                          OutputIterator2                            values_result);


template<typename ExecutionPolicy,
         typename InputIterator1,
         typename InputIterator2,
         typename InputIterator3,
         typename OutputIterator1,
         typename OutputIterator2,
         typename StrictWeakOrdering>
__hydra_host__ __hydra_device__
HYDRA_EXTERNAL_NS::thrust::pair<OutputIterator1,OutputIterator2>
  set_intersection_by_key(HYDRA_EXTERNAL_NS::thrust::execution_policy<ExecutionPolicy> &system,
                          InputIterator1                             keys_first1,
                          InputIterator1                             keys_last1,
                          InputIterator2                             keys_first2,
                          InputIterator2                             keys_last2,
                          InputIterator3                             values_first1,
                          OutputIterator1                            keys_result,
                          OutputIterator2                            values_result,
                          StrictWeakOrdering                         comp);


template<typename ExecutionPolicy,
         typename InputIterator1,
         typename InputIterator2,
         typename OutputIterator>
__hydra_host__ __hydra_device__
OutputIterator set_symmetric_difference(HYDRA_EXTERNAL_NS::thrust::execution_policy<ExecutionPolicy> &system,
                                        InputIterator1                             first1,
                                        InputIterator1                             last1,
                                        InputIterator2                             first2,
                                        InputIterator2                             last2,
                                        OutputIterator                             result);


// XXX it is an error to call this function; it has no implementation
template<typename ExecutionPolicy,
         typename InputIterator1,
         typename InputIterator2,
         typename OutputIterator,
         typename StrictWeakOrdering>
__hydra_host__ __hydra_device__
OutputIterator set_symmetric_difference(HYDRA_EXTERNAL_NS::thrust::execution_policy<ExecutionPolicy> &system,
                                        InputIterator1                             first1,
                                        InputIterator1                             last1,
                                        InputIterator2                             first2,
                                        InputIterator2                             last2,
                                        OutputIterator                             result,
                                        StrictWeakOrdering                         comp);


template<typename ExecutionPolicy,
         typename InputIterator1,
         typename InputIterator2,
         typename InputIterator3,
         typename InputIterator4,
         typename OutputIterator1,
         typename OutputIterator2>
__hydra_host__ __hydra_device__
HYDRA_EXTERNAL_NS::thrust::pair<OutputIterator1,OutputIterator2>
  set_symmetric_difference_by_key(HYDRA_EXTERNAL_NS::thrust::execution_policy<ExecutionPolicy> &system,
                                  InputIterator1                             keys_first1,
                                  InputIterator1                             keys_last1,
                                  InputIterator2                             keys_first2,
                                  InputIterator2                             keys_last2,
                                  InputIterator3                             values_first1,
                                  InputIterator4                             values_first2,
                                  OutputIterator1                            keys_result,
                                  OutputIterator2                            values_result);


template<typename ExecutionPolicy,
         typename InputIterator1,
         typename InputIterator2,
         typename InputIterator3,
         typename InputIterator4,
         typename OutputIterator1,
         typename OutputIterator2,
         typename StrictWeakOrdering>
__hydra_host__ __hydra_device__
HYDRA_EXTERNAL_NS::thrust::pair<OutputIterator1,OutputIterator2>
  set_symmetric_difference_by_key(HYDRA_EXTERNAL_NS::thrust::execution_policy<ExecutionPolicy> &system,
                                  InputIterator1                             keys_first1,
                                  InputIterator1                             keys_last1,
                                  InputIterator2                             keys_first2,
                                  InputIterator2                             keys_last2,
                                  InputIterator3                             values_first1,
                                  InputIterator4                             values_first2,
                                  OutputIterator1                            keys_result,
                                  OutputIterator2                            values_result,
                                  StrictWeakOrdering                         comp);


template<typename ExecutionPolicy,
         typename InputIterator1,
         typename InputIterator2,
         typename OutputIterator>
__hydra_host__ __hydra_device__
OutputIterator set_union(HYDRA_EXTERNAL_NS::thrust::execution_policy<ExecutionPolicy> &system,
                         InputIterator1                             first1,
                         InputIterator1                             last1,
                         InputIterator2                             first2,
                         InputIterator2                             last2,
                         OutputIterator                             result);


// XXX it is an error to call this function; it has no implementation
template<typename ExecutionPolicy,
         typename InputIterator1,
         typename InputIterator2,
         typename OutputIterator,
         typename StrictWeakOrdering>
__hydra_host__ __hydra_device__
OutputIterator set_union(HYDRA_EXTERNAL_NS::thrust::execution_policy<ExecutionPolicy> &system,
                         InputIterator1                             first1,
                         InputIterator1                             last1,
                         InputIterator2                             first2,
                         InputIterator2                             last2,
                         OutputIterator                             result,
                         StrictWeakOrdering                         comp);


template<typename ExecutionPolicy,
         typename InputIterator1,
         typename InputIterator2,
         typename InputIterator3,
         typename InputIterator4,
         typename OutputIterator1,
         typename OutputIterator2>
__hydra_host__ __hydra_device__
HYDRA_EXTERNAL_NS::thrust::pair<OutputIterator1,OutputIterator2>
  set_union_by_key(HYDRA_EXTERNAL_NS::thrust::execution_policy<ExecutionPolicy> &system,
                   InputIterator1                             keys_first1,
                   InputIterator1                             keys_last1,
                   InputIterator2                             keys_first2,
                   InputIterator2                             keys_last2,
                   InputIterator3                             values_first1,
                   InputIterator4                             values_first2,
                   OutputIterator1                            keys_result,
                   OutputIterator2                            values_result);


template<typename ExecutionPolicy,
         typename InputIterator1,
         typename InputIterator2,
         typename InputIterator3,
         typename InputIterator4,
         typename OutputIterator1,
         typename OutputIterator2,
         typename StrictWeakOrdering>
__hydra_host__ __hydra_device__
HYDRA_EXTERNAL_NS::thrust::pair<OutputIterator1,OutputIterator2>
  set_union_by_key(HYDRA_EXTERNAL_NS::thrust::execution_policy<ExecutionPolicy> &system,
                   InputIterator1                             keys_first1,
                   InputIterator1                             keys_last1,
                   InputIterator2                             keys_first2,
                   InputIterator2                             keys_last2,
                   InputIterator3                             values_first1,
                   InputIterator4                             values_first2,
                   OutputIterator1                            keys_result,
                   OutputIterator2                            values_result,
                   StrictWeakOrdering                         comp);


} // end namespace generic
} // end namespace detail
} // end namespace system
} // end HYDRA_EXTERNAL_NAMESPACE_BEGIN  namespace thrust
HYDRA_EXTERNAL_NAMESPACE_END
#include <hydra/detail/external/thrust/system/detail/generic/set_operations.inl>

