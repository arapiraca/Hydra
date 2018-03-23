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

HYDRA_EXTERNAL_NAMESPACE_BEGIN  namespace thrust
{
namespace system
{
namespace detail
{
namespace generic
{


template<typename DerivedPolicy, typename InputIterator1, typename InputIterator2, typename OutputType>
__hydra_host__ __hydra_device__
  OutputType inner_product(thrust::execution_policy<DerivedPolicy> &exec,
                           InputIterator1 first1,
                           InputIterator1 last1,
                           InputIterator2 first2,
                           OutputType init);


template<typename DerivedPolicy, typename InputIterator1, typename InputIterator2, typename OutputType, typename BinaryFunction1, typename BinaryFunction2>
__hydra_host__ __hydra_device__
OutputType inner_product(thrust::execution_policy<DerivedPolicy> &exec,
                         InputIterator1 first1,
                         InputIterator1 last1,
                         InputIterator2 first2,
                         OutputType init, 
                         BinaryFunction1 binary_op1,
                         BinaryFunction2 binary_op2);


} // end namespace generic
} // end namespace detail
} // end namespace system
} // end HYDRA_EXTERNAL_NAMESPACE_BEGIN  namespace thrust

HYDRA_EXTERNAL_NAMESPACE_END

#include <hydra/detail/external/thrust/system/detail/generic/inner_product.inl>
