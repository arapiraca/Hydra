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
#include <hydra/detail/external/thrust/system/detail/generic/copy.h>
#include <hydra/detail/external/thrust/functional.h>
#include <hydra/detail/external/thrust/detail/internal_functional.h>
#include <hydra/detail/external/thrust/transform.h>
#include <hydra/detail/external/thrust/for_each.h>
#include <hydra/detail/external/thrust/tuple.h>
#include <hydra/detail/external/thrust/iterator/zip_iterator.h>
#include <hydra/detail/external/thrust/iterator/detail/minimum_system.h>

HYDRA_EXTERNAL_NAMESPACE_BEGIN  namespace thrust
{
namespace system
{
namespace detail
{
namespace generic
{


template<typename DerivedPolicy,
         typename InputIterator,
         typename OutputIterator>
__hydra_host__ __hydra_device__
  OutputIterator copy(HYDRA_EXTERNAL_NS::thrust::execution_policy<DerivedPolicy> &exec,
                      InputIterator                            first,
                      InputIterator                            last,
                      OutputIterator                           result)
{
  typedef typename HYDRA_EXTERNAL_NS::thrust::iterator_value<InputIterator>::type T;
  return HYDRA_EXTERNAL_NS::thrust::transform(exec, first, last, result, HYDRA_EXTERNAL_NS::thrust::identity<T>());
} // end copy()


template<typename DerivedPolicy,
         typename InputIterator,
         typename Size,
         typename OutputIterator>
__hydra_host__ __hydra_device__
  OutputIterator copy_n(HYDRA_EXTERNAL_NS::thrust::execution_policy<DerivedPolicy> &exec,
                        InputIterator                            first,
                        Size                                     n,
                        OutputIterator                           result)
{
  typedef typename HYDRA_EXTERNAL_NS::thrust::iterator_value<InputIterator>::type value_type;
  typedef HYDRA_EXTERNAL_NS::thrust::identity<value_type>                         xfrm_type;

  typedef HYDRA_EXTERNAL_NS::thrust::detail::unary_transform_functor<xfrm_type> functor_type;

  typedef HYDRA_EXTERNAL_NS::thrust::tuple<InputIterator,OutputIterator> iterator_tuple;
  typedef HYDRA_EXTERNAL_NS::thrust::zip_iterator<iterator_tuple>        zip_iter;

  zip_iter zipped = HYDRA_EXTERNAL_NS::thrust::make_zip_iterator(HYDRA_EXTERNAL_NS::thrust::make_tuple(first,result));

  return HYDRA_EXTERNAL_NS::thrust::get<1>(HYDRA_EXTERNAL_NS::thrust::for_each_n(exec, zipped, n, functor_type(xfrm_type())).get_iterator_tuple());
} // end copy_n()


} // end generic
} // end detail
} // end system
} // end HYDRA_EXTERNAL_NAMESPACE_BEGIN  namespace thrust

HYDRA_EXTERNAL_NAMESPACE_END
