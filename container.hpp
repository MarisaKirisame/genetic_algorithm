#ifndef GENETIC_ALGORITHM_CONTAINER_HPP
#define GENETIC_ALGORITHM_PARAMETER_HPP
#include <algorithm>
namespace genetic_algorithm
{
	template< typename CRTP >
	struct container
	{
		template<class Archive>
		void serialize( Archive &, const unsigned int ) { }
		void mutate( double mr )
		{
			auto begin = static_cast< CRTP * >( this )->get_begin( );
			auto end = static_cast< CRTP * >( this )->get_end( );
			for ( ;begin != end; ++ begin ) { begin->mutate( mr ); }
		}
		void mutate( )
		{
			auto begin = static_cast< CRTP * >( this )->get_begin( );
			auto end = static_cast< CRTP * >( this )->get_end( );
			for ( ;begin != end; ++ begin ) { begin->mutate( ); }
		}
		void crossover( const container & c )
		{
			auto begin = static_cast< CRTP * >( this )->get_begin( );
			auto end = static_cast< CRTP * >( this )->get_end( );
			auto cbegin = static_cast< const CRTP & >( c ).get_begin( );
			auto cend = static_cast< const CRTP & >( c ).get_end( );
		}
	};
}
#endif //GENETIC_ALGORITHM_PARAMETER_HPP
