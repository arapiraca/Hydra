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


/*! \file distance.inl
 *  \brief Inline file for distance.h
 */

#include <hydra/detail/external/hydra_thrust/advance.h>
#include <hydra/detail/external/hydra_thrust/system/detail/generic/distance.h>
#include <hydra/detail/external/hydra_thrust/iterator/iterator_traits.h>

namespace hydra_thrust
{


template<typename InputIterator>
inline __host__ __device__
  typename hydra_thrust::iterator_traits<InputIterator>::difference_type
    distance(InputIterator first, InputIterator last)
{
  return hydra_thrust::system::detail::generic::distance(first, last);
} // end distance()


} // end namespace hydra_thrust
