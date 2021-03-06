/*----------------------------------------------------------------------------
 *
 *   Copyright (C) 2016 - 2020 Antonio Augusto Alves Junior
 *
 *   This file is part of Hydra Data Analysis Framework.
 *
 *   Hydra is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   Hydra is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Hydra.  If not, see <http://www.gnu.org/licenses/>.
 *
 *---------------------------------------------------------------------------*/

/*
 * RandonRange.inl
 *
 *  Created on: 20/05/2018
 *      Author: Antonio Augusto Alves Junior
 */

#ifndef RANDONRANGE_INL_
#define RANDONRANGE_INL_



#include <hydra/detail/Config.h>
#include <hydra/detail/functors/RandomUtils.h>
#include <hydra/detail/external/hydra_thrust/iterator/constant_iterator.h>
#include <hydra/detail/external/hydra_thrust/iterator/transform_iterator.h>


namespace hydra {

template<typename Value_Type>
Range<hydra_thrust::transform_iterator<
detail::RndGauss<Value_Type, hydra_thrust::random::default_random_engine> ,
hydra_thrust::counting_iterator<size_t>, Value_Type>>
random_gauss_range(Value_Type  mean, Value_Type  width, size_t seed, size_t length=0 ){

	// create iterators
	typedef hydra_thrust::counting_iterator<size_t> index_t;
	typedef detail::RndGauss<Value_Type, hydra_thrust::random::default_random_engine> gauss_t;

	index_t first(0);
	index_t last( length==0 ? std::numeric_limits<size_t>::max() : length);

	return make_range(
			hydra_thrust::transform_iterator<gauss_t, index_t, Value_Type>(first, gauss_t(seed, mean, width )),
	        hydra_thrust::transform_iterator<gauss_t, index_t, Value_Type>( last, gauss_t(seed, mean, width )));
}

template<typename Value_Type>
Range<hydra_thrust::transform_iterator<
detail::RndUniform<Value_Type, hydra_thrust::random::default_random_engine> ,
hydra_thrust::counting_iterator<size_t>, Value_Type>>
random_uniform_range(const Value_Type& min, const Value_Type& max, size_t seed, size_t length=0 ){

	// create iterators
	typedef hydra_thrust::counting_iterator<size_t> index_t;
	typedef detail::RndUniform<Value_Type, hydra_thrust::random::default_random_engine> uniform_t;

	index_t first(0);
	index_t last( length==0 ? std::numeric_limits<size_t>::max() : length);

	return make_range(
			hydra_thrust::transform_iterator<uniform_t, index_t, Value_Type>(first, uniform_t(seed, min, max )),
	        hydra_thrust::transform_iterator<uniform_t, index_t, Value_Type>( last, uniform_t(seed, min, max )));

}


template<typename Value_Type>
Range<hydra_thrust::transform_iterator<
detail::RndExp<Value_Type, hydra_thrust::random::default_random_engine> ,
hydra_thrust::counting_iterator<size_t>, double>>
random_exp_range(const Value_Type& tau,  size_t seed, size_t length=0 ){

	// create iterators
	typedef hydra_thrust::counting_iterator<size_t> index_t;
	typedef detail::RndExp<Value_Type, hydra_thrust::random::default_random_engine> exp_t;

	index_t first(0);
	index_t last( length==0 ? std::numeric_limits<size_t>::max() : length);

	return make_range(
			hydra_thrust::transform_iterator<exp_t, index_t, double>(first, exp_t(seed, tau )),
	        hydra_thrust::transform_iterator<exp_t, index_t, double>( last, exp_t(seed, tau )));
}



}  // namespace hydra

#endif /* RANDONRANGE_INL_ */
