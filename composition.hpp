#ifndef GENETIC_ALGORITHM_COMPOSITION_HPP
#define GENETIC_ALGORITHM_COMPOSITION_HPP
namespace genetic_algorithm
{
	template< typename CRTP >
	struct composition
	{
		template<class Archive>
		void serialize( Archive &, const unsigned int ) { }
		void mutate( double mr )
		{
			auto dat = static_cast< CRTP * >( this )->get_data( );
			dat.first.mutate( mr );
			dat.second.mutate( mr );
		}

		void mutate( )
		{
			auto dat = static_cast< CRTP * >( this )->get_data( );
			dat.first.mutate( );
			dat.second.mutate( );
		}

		void crossover( const composition & c )
		{
			auto dat = static_cast< CRTP * >( this )->get_data( );
			auto datc = static_cast< const CRT & >( c ).get_data( );
			dat.first.crossover( datc.first );
			dat.second.crossover( datc.second );
		}
	};
}
#endif //GENETIC_ALGORITHM_COMPOSITION_HPP
