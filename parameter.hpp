#ifndef GENETIC_ALGORITHM_PARAMETER_HPP
#define GENETIC_ALGORITHM_PARAMETER_HPP
#include "random.hpp"
namespace genetic_algorithm
{
	template< typename t >
	struct no_default
	{
		t data;
		no_default( ) = delete;
		template < typename ... R >
		no_default( R ... r ) : data( r ... ) { }
		template<class Archive>
		void serialize( Archive &, const unsigned int ) { }
	};
}

namespace boost
{
	namespace serialization
	{
		template< class Archive, typename T >
		void save_construct_data( Archive & ar, const genetic_algorithm::no_default< T > * t, const unsigned long int ) { ar << t->data; }

		template< class Archive, typename T >
		void load_construct_data( Archive & ar, const genetic_algorithm::no_default< T > * t, const unsigned long int )
		{
			T m;
			ar >> m;
			::new(t)genetic_algorithm::no_default< T >( m );
		}
	}
}

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
		void serialize( Archive &, const unsigned int ) { }
	};
	template< typename t > struct optional< t, false >
	{
		template<class Archive>
		void serialize( Archive &, const unsigned int ) { }
	};
}

namespace boost
{
	namespace serialization
	{
		template< class Archive, typename T >
		void save_construct_data( Archive & ar, const genetic_algorithm::optional< T, true > * t, const unsigned long int ) { ar << t->data; }

		template< class Archive, typename T >
		void load_construct_data( Archive & ar, const genetic_algorithm::optional< T, true > * t, const unsigned long int )
		{
			T m;
			ar >> m;
			::new(t)genetic_algorithm::optional< T, true >( m );
		}
	}
}

namespace genetic_algorithm
{
	template< typename t, bool internal_mutate_rate = true >
	struct parameter
	{
		t data;
		optional< no_default< double >, internal_mutate_rate > mr;
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
	};
}
#endif //GENETIC_ALGORITHM_PARAMETER_HPP
