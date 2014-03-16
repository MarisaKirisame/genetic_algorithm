#ifndef GENETIC_ALGORITHM_COMPOSITION_HPP
#define GENETIC_ALGORITHM_COMPOSITION_HPP
namespace genetic_algorithm
{
	template< typename CRTP, typename l1, typename l2 >
	struct composition
	{
		template<class Archive>
		void serialize( Archive & ar, const unsigned int )
		{
			auto dat = static_cast< CRTP * >( this )->get_data( );
			ar & dat.first;
			ar & dat.second;
		}
		void mutate( double mr )
		{
			auto dat = static_cast< CRTP * >( this )->get_data( );
			data.first.mutate( mr );
			data.second.mutate( mr );
		}

		void mutate( )
		{
			auto dat = static_cast< CRTP * >( this )->get_data( );
			data.first.mutate( );
			data.second.mutate( );
		}
	};
}
#endif //GENETIC_ALGORITHM_COMPOSITION_HPP
