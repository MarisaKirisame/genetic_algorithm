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
	};
}
#endif //GENETIC_ALGORITHM_PARAMETER_HPP
