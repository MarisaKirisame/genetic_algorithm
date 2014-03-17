#ifndef GENETIC_ALGORITHM_PARAMETER_HPP
#define GENETIC_ALGORITHM_PARAMETER_HPP
#include "random.hpp"
namespace genetic_algorithm
{
	template< typename t, bool have_data >
	struct optional;

	template< typename t > struct optional< t, true >
	{
		t data;
		template < typename ret >
		explicit operator ret( ) { return static_cast< ret >( data ); }
		template < typename ... R >
		optional( R ... r ) : data( r ... ) { }
		template<class Archive>
		void serialize( Archive & ar, const unsigned int ) { ar & data; }
	};

	template< typename t > struct optional< t, false >
	{
		template<class Archive>
		void serialize( Archive &, const unsigned int ) { }
	};

	template< typename t, bool internal_mutate_rate = true >
	struct parameter
	{
		t data;
		optional< double, internal_mutate_rate > mr;
		void mutate( double mr )
		{
			if ( random::random_bool( ) ) { data *= ( 1 + random::random_probability( ) * mr * 2 ); }
			else { data /= ( 1 + random::random_probability( ) * mr * 2 ); }
		}

		void mutate( )
		{
			mutate( static_cast< double >( mr ) );
			if ( random::random_bool( ) ) { mr.data *= ( 1 + random::random_probability( ) * static_cast< double >( mr ) * 2 ); }
			else { mr.data /= ( 1 + random::random_probability( ) * static_cast< double >( mr ) * 2 ); }
		}

		void crossover( const parameter & pa )
		{
			if ( random::random_bool( ) ) { data = pa.data; }
			if ( random::random_bool( ) ) { mr = pa.mr; }
		}

		template<class Archive>
		void serialize( Archive & ar, const unsigned int )
		{
			ar & data;
			ar & mr;
		}

		parameter( const t & data, double mr ) : data( data ), mr( mr ) { }
		parameter( t && data, double mr ) : data( std::move( data ) ), mr( mr ) { }
		parameter( const t & data ) : data( data ) { }
		parameter( t && data ) : data( std::move( data ) ) { }

		template< typename tt >
		explicit operator tt ( ) const { return static_cast< tt >( data ); }
	};
}
#endif //GENETIC_ALGORITHM_PARAMETER_HPP
