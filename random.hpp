#ifndef GENETIC_ALGORITHM_RANDOM_HPP
#define GENETIC_ALGORITHM_RANDOM_HPP
#include <random>
namespace genetic_algorithm
{
	struct random
	{
		static constexpr double weight_min = -1;
		static constexpr double weight_max = +1;
		static std::random_device & device( ) { static std::random_device ret; return ret; }
		static double random_weight( )
		{
			static std::uniform_real_distribution< double > ret( weight_min, weight_max );
			return ret( device( ) );
		}
		static double random_probability( )
		{
			static std::uniform_real_distribution< double > urd( 0, 1 );
			return urd( device( ) );
		}
		static bool random_bool( )
		{
			static std::uniform_int_distribution< size_t > uid( 0, 1 );
			return uid( device( ) ) == 1;
		}
	};
}
#endif // GENETIC_ALGORITHM_RANDOM_HPP
