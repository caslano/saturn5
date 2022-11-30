
///////////////////////////////////////////////////////////////////////////////
// density.hpp
//
//  Copyright 2006 Daniel Egloff, Olivier Gygi. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_DENSITY_HPP_DE_01_01_2006
#define BOOST_ACCUMULATORS_STATISTICS_DENSITY_HPP_DE_01_01_2006

#include <vector>
#include <limits>
#include <functional>
#include <boost/range.hpp>
#include <boost/parameter/keyword.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/accumulators/accumulators_fwd.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/numeric/functional.hpp>
#include <boost/accumulators/framework/parameters/sample.hpp>
#include <boost/accumulators/framework/depends_on.hpp>
#include <boost/accumulators/statistics_fwd.hpp>
#include <boost/accumulators/statistics/count.hpp>
#include <boost/accumulators/statistics/max.hpp>
#include <boost/accumulators/statistics/min.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/utility.hpp>

namespace boost { namespace accumulators
{

///////////////////////////////////////////////////////////////////////////////
// cache_size and num_bins named parameters
//
BOOST_PARAMETER_NESTED_KEYWORD(tag, density_cache_size, cache_size)
BOOST_PARAMETER_NESTED_KEYWORD(tag, density_num_bins, num_bins)

BOOST_ACCUMULATORS_IGNORE_GLOBAL(density_cache_size)
BOOST_ACCUMULATORS_IGNORE_GLOBAL(density_num_bins)

namespace impl
{
    ///////////////////////////////////////////////////////////////////////////////
    // density_impl
    //  density histogram
    /**
        @brief Histogram density estimator

        The histogram density estimator returns a histogram of the sample distribution. The positions and sizes of the bins
        are determined using a specifiable number of cached samples (cache_size). The range between the minimum and the
        maximum of the cached samples is subdivided into a specifiable number of bins (num_bins) of same size. Additionally,
        an under- and an overflow bin is added to capture future under- and overflow samples. Once the bins are determined,
        the cached samples and all subsequent samples are added to the correct bins. At the end, a range of std::pair is
        return, where each pair contains the position of the bin (lower bound) and the samples count (normalized with the
        total number of samples).

        @param  density_cache_size Number of first samples used to determine min and max.
        @param  density_num_bins Number of bins (two additional bins collect under- and overflow samples).
    */
    template<typename Sample>
    struct density_impl
      : accumulator_base
    {
        typedef typename numeric::functional::fdiv<Sample, std::size_t>::result_type float_type;
        typedef std::vector<std::pair<float_type, float_type> > histogram_type;
        typedef std::vector<float_type> array_type;
        // for boost::result_of
        typedef iterator_range<typename histogram_type::iterator> result_type;

        template<typename Args>
        density_impl(Args const &args)
            : cache_size(args[density_cache_size])
            , cache(cache_size)
            , num_bins(args[density_num_bins])
            , samples_in_bin(num_bins + 2, 0.)
            , bin_positions(num_bins + 2)
            , histogram(
                num_bins + 2
              , std::make_pair(
                    numeric::fdiv(args[sample | Sample()],(std::size_t)1)
                  , numeric::fdiv(args[sample | Sample()],(std::size_t)1)
                )
              )
            , is_dirty(true)
        {
        }

        template<typename Args>
        void operator ()(Args const &args)
        {
            this->is_dirty = true;

            std::size_t cnt = count(args);

            // Fill up cache with cache_size first samples
            if (cnt <= this->cache_size)
            {
                this->cache[cnt - 1] = args[sample];
            }

            // Once cache_size samples have been accumulated, create num_bins bins of same size between
            // the minimum and maximum of the cached samples as well as under and overflow bins.
            // Store their lower bounds (bin_positions) and fill the bins with the cached samples (samples_in_bin).
            if (cnt == this->cache_size)
            {
                float_type minimum = numeric::fdiv((min)(args), (std::size_t)1);
                float_type maximum = numeric::fdiv((max)(args), (std::size_t)1);
                float_type bin_size = numeric::fdiv(maximum - minimum, this->num_bins );

                // determine bin positions (their lower bounds)
                for (std::size_t i = 0; i < this->num_bins + 2; ++i)
                {
                    this->bin_positions[i] = minimum + (i - 1.) * bin_size;
                }

                for (typename array_type::const_iterator iter = this->cache.begin(); iter != this->cache.end(); ++iter)
                {
                    if (*iter < this->bin_positions[1])
                    {
                        ++(this->samples_in_bin[0]);
                    }
                    else if (*iter >= this->bin_positions[this->num_bins + 1])
                    {
                        ++(this->samples_in_bin[this->num_bins + 1]);
                    }
                    else
                    {
                        typename array_type::iterator it = std::upper_bound(
                            this->bin_positions.begin()
                          , this->bin_positions.end()
                          , *iter
                        );

                        std::size_t d = std::distance(this->bin_positions.begin(), it);
                        ++(this->samples_in_bin[d - 1]);
                    }
                }
            }
            // Add each subsequent sample to the correct bin
            else if (cnt > this->cache_size)
            {
                if (args[sample] < this->bin_positions[1])
                {
                    ++(this->samples_in_bin[0]);
                }
                else if (args[sample] >= this->bin_positions[this->num_bins + 1])
                {
                    ++(this->samples_in_bin[this->num_bins + 1]);
                }
                else
                {
                    typename array_type::iterator it = std::upper_bound(
                        this->bin_positions.begin()
                      , this->bin_positions.end()
                      , args[sample]
                    );

                    std::size_t d = std::distance(this->bin_positions.begin(), it);
                    ++(this->samples_in_bin[d - 1]);
                }
            }
        }

        /**
            @pre The number of samples must meet or exceed the cache size
        */
        template<typename Args>
        result_type result(Args const &args) const
        {
            if (this->is_dirty)
            {
                this->is_dirty = false;

                // creates a vector of std::pair where each pair i holds
                // the values bin_positions[i] (x-axis of histogram) and
                // samples_in_bin[i] / cnt (y-axis of histogram).

                for (std::size_t i = 0; i < this->num_bins + 2; ++i)
                {
                    this->histogram[i] = std::make_pair(this->bin_positions[i], numeric::fdiv(this->samples_in_bin[i], count(args)));
                }
            }
            // returns a range of pairs
            return make_iterator_range(this->histogram);
        }

        // make this accumulator serializeable
        // TODO split to save/load and check on parameters provided in ctor
        template<class Archive>
        void serialize(Archive & ar, const unsigned int file_version)
        {
            ar & cache_size;
            ar & cache;
            ar & num_bins;
            ar & samples_in_bin;
            ar & bin_positions;
            ar & histogram;
            ar & is_dirty; 
        }

    private:
        std::size_t            cache_size;      // number of cached samples
        array_type             cache;           // cache to store the first cache_size samples
        std::size_t            num_bins;        // number of bins
        array_type             samples_in_bin;  // number of samples in each bin
        array_type             bin_positions;   // lower bounds of bins
        mutable histogram_type histogram;       // histogram
        mutable bool is_dirty;
    };

} // namespace impl

///////////////////////////////////////////////////////////////////////////////
// tag::density
//
namespace tag
{
    struct density
      : depends_on<count, min, max>
      , density_cache_size
      , density_num_bins
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::density_impl<mpl::_1> impl;

        #ifdef BOOST_ACCUMULATORS_DOXYGEN_INVOKED
        /// tag::density::cache_size named parameter
        /// tag::density::num_bins named parameter
        static boost::parameter::keyword<density_cache_size> const cache_size;
        static boost::parameter::keyword<density_num_bins> const num_bins;
        #endif
    };
}

///////////////////////////////////////////////////////////////////////////////
// extract::density
//
namespace extract
{
    extractor<tag::density> const density = {};

    BOOST_ACCUMULATORS_IGNORE_GLOBAL(density)
}

using extract::density;

// So that density can be automatically substituted
// with weighted_density when the weight parameter is non-void.
template<>
struct as_weighted_feature<tag::density>
{
    typedef tag::weighted_density type;
};

template<>
struct feature_of<tag::weighted_density>
  : feature_of<tag::density>
{
};

}} // namespace boost::accumulators

#endif

/* density.hpp
iwGPj+v/xe7dDX7/b9XdEE8UEPQQLd8TH7G7hsgnzSb5npHkPB2x6Q6vFoKZ95kc4RVhOKt4tR6xXTOkUdzGlUSX0z/0JJXcZYXqVoQIE/ZpwJ8JKFOKMhn21H9TjUn26HzoVrofxR6a75WRgNgl7Yeh8q1ec7Ov4o4lf/+WdRgt3av3pqP6qaX6qTfCoK3De/v0pcT8XiRH/BhcnRW8fvHQdBqkmao25vn84bKoPH7T+/7czcdZUxOMrzi4VeT+6bzhO/Ir/9YL+SX8/U3mo57EOY6kEyK40Uxu5P69gvgqtKoyzIE2Tf794h6KQnDBQnnkITzxEpp6DUnzwzH8kfj3XkpoemQ0FnunTYmG/HkEsjrIDrqr+WaoNxtM98HDCjFC+8Y6iP5pz+sdTzftfyv8Bj+7khGPjud/a3Lng9ijtKcFpYe4265xJ4JXGEa3FK/FJmU14v24H2kGvrDvxRUaRNcjqsGsYSW6g8dGtRb2eGI5zQFIB5wDygHj//e7sygAXp/8z4giAGqPug/TfxFABhQDggPEDmuPuAfgR+/D8zcDwgNxh9wDIvnyAeACqgHc/DR9nP5/vTlQCPAJkPXR/MEIBPGLZI6EKhOaTYuihb0jy2/0BlmP0ScWaYtdpNbk6GA27LOWlBYPhMwvb7YcT5MjPu12DXZxYxtuX3azBFCc0rW0zj8xgm933k9kpcwNCXuvia4yy71/H+xCZxV7Ogm+qBByfdyhX/sHFwbZvvXfpqq5xpqQOIcm2Fa7LPZXes59nfAeYeF+L8ZbZ7WP2tq1NKZWwEMzA2bTc8qyca1+cn/WnX52h/3ywM3B+Ze1hvXKOJZssEZvtNrijb7v0AF+QP4WZK8kfe5l6n/5CfvAZejhd/j8D99JY95AX6nDqK5xXsEA0EyrICiApZ/bIYJfv+9FZDhSRg4UlyQF+GM8f7oJVjJUnv49uUHzF64b8INBcLjxhiwRIc9Q7YrQYrMwugkz2re/euACraijMRDM1LmlzKkl6LJuxrigbl1EV7DeCjPYgbWsWcopWi532UB63lCMSp/bjgdALQm3DmJ4q33KJz2HOx8gN6/f/p9CfHs/Swhtbv914/Ht+R5BbkD49vDS6LUPbH+A3CYR2sh+/L1OENo2/fp8cNvw35tTpODPZzPx5xwVxcdcenFsZj9j518+fRk2ct5yC6/rEWJanHqxbFJp69m+lKWc4J7dEK9yQ9fYfrUnv2nMj113a0l0i3+u+BYd1cKWyJ7RCxeZAArCYWud4kMCUUWD2qdMGU7y7DWAE040f+iaGKu/SqjbHvIyP9VZaKWiWyr0gxsQTGlyzg3eZOhfLg4QFNv2tjRssV45J3S/sh1Ga0mR4ibo/9WwTlYEKilm7F+fyOIP34QetqtX8gfVge5O7U57pwpfXalvPkgHEDhBX4bsfyY44K/SdqHHNL4Z/HTvVxP8WJN9eZK0dVJCPloauO9evToeof1+K3osf861H/hk9Gr3SGBNqxAE2vod+jsqbf6AI50K0Ud+UQ7J2UCAHLEjmCa6Udz8Vmj3u84NvnHcQmwQIh3tYRZuCDwvDpp78h09OPzbFdpyHaaD+IpaEt1E7V2R+ipC5JMhmMbut+M+RZBQGs7Fu7ib3ajVvP8luxZzN3QK6p3DDXj7VHNXdODDq3Pgm+oS+gzQbCG/ifDTbCGJ6I35gknWkgj8yUT5xafk+ulooy3GP7RDR69t++087kWa+DVKo9DZiDWz/68qFSjUL2UZ8nuqTfZoaWlA+AERUlND954XKfltExfF/yJL/BrWcaz+cfO1hA+F/2jOYO23m6Tb2+yLXm+C6jFqYdlL/ZyfM4XvfQui00KwNqlvx5863S0v5dC3/N7xNMStr/lFfcZpDPeFI1XVe2sxPMZW727Ly84vFCg3C8L6DVv43W3JyVKUO8Gpei1++V28hLoe2Wgc7OuJyJbUf/tV4IG7C/LUF8XxvUc3VPv+ZaslCw3NVdjnGqnfnZs13xDr9dusQbmyX+3xkVMYiDsp9ti/9VPh0fAcGazCbsFjVeiHgI81QWXIyDF8xuDifymV/lSHVe0NGKReUwqbjzn/ylWS++NbHcYxaPuFKYOzIULE9r+DoEEOwM/c1oT5bug3ynPMDaCw6aalphEuLYHGjsRJ9c+/+7CAU979jkqxTelNgwOggBLagPUZ+4D9ZQCt/JXBucDuyADSmX0da7kDxT78y4TfD7YiqAHA6B5sP2u7VIAqQBaICRAyeGcEQAMZK9wvqPoLcBui9mcawpiZ+/GaP/6NyE1fMWGXOUgTVjKUPggcChx6DvcT/5I66BHe3hp3qs3I5GTzuploT53NZKn13QF59OW6HfeYnfnc7Or3QE6skXkgvRb3ZLXQW8hNyJXxJWrne8809pE0jqAgYT2uSCpKWkqaSgpMKkhyoaCh2EnKLeJOf7CeqE+CeiSbjc3l8/Jd+Cp4tzptnbpN++18p5viY/wd8Pb4SQOLRKPW29OWb+RXn+vYGwdbLhe0NLuIVcKX+Pa5yFkKKscv0k01lWksRi3dThgpfS7BlZLSUG+qs9z3gcHXdtffnw/Bp8sykKmnbdrRd9GcrFZZ0bRqXLb6rn9uXbGrNlqYPlcr1kvNSbCVsRPvZfq+eYJYyJX2I/XR+6h/al3kE/9l1sk0GEvL+pPKwGNkOlIA6zVSjRmNiWDSFcdgMJ8cmYBOo53UbD5cUCEyHSlL42n3hxFDe1E7h93npqX9zyPpbCdtOc35qETyeCvpL6mH2cNtQq74j9ID0/gsyS+Ph56jnKPeg9R4LXFvxpfnQ/mRW8Ku3A/5eu6XxkPqODrAzLGB1sRiIiIpIekh6dq/FEIJT8aD1sRO0m6Ci6LjPfQd+USPl8/op+K9+JHq5Nf7p/aEj9Xv9Wv2VIymjjqtk8CuH6tP5THQC01aprmEVopGwkZ6O9WTvJn8uqSJbOGlCFcOW3KRust63wUmG4YK7cd2Hx+9p45+hRO7TtlmW797+wP78rb6VmtWKwyIz+GcaTFxAb00tUStxE7cTnI3xVetI+0H/1yuNFdiFtx7K2k+vZ7p8D2KjfELs0PEIdKUukKnyUXhtCCX7uOxQCgyhjYBTYS2x/H+OZIJPZW2x6i+7Q09El/L293h92AW3amprA3+Ljm97W89833LUC4Jb9qbveHaVll74gnpTDYfW3aZ9fbWRbvWScv0ddZnWLvc7DZPq5ft7hbbaQ/Xa2H76WlMbqu17mgXxOm3w86PB90MF+dttsdC16P/c1FRiIRUgq1cB9O59AKZhJDExlH4+Pm4yPjx+PM4n9yPysNuQiypX9wA0DTqdK/XT9Ajfvrv6Ltf+u/rO920n4/v7xfdSexUrDa9Qf8SWBh6lvbdTuDdUtlSSLmUIowildJ2eabirey3jKXdxf6SUfluycUitcVryTfjNZtFbClP8ktq07fFrzhX/IvsBoRFPAwZTZfh/jMMOnUTHbXemc6bU95IKhqpOro6uobNiuRlNX9Ib3OPQbRMLkTTKrD7t8VH7aJf7o+yp/tIVdRW1FeUCmZN1EfUNCbf9JvJSCGm35g7bSHdoXtoEkPan2bzk4IpETY6S82llrPRSDzdp1iRUnQR6py2tYa3jWE+ra/fJqcUPz2U39deSIvzG1tjUzNXU1cz17Ab2WIpi6L2OFv5IRgBzmKhDi4wUNq4OJS3uW1gpAeu29ZdvgO3wVfc23d9PSfdU+7ZmQFVr76dZjkb4qsagylMCYuFtCYCmHHohnTlknpn0G3Z2IUw5hGJExS3CXY9dprsqS5EBA+RH5JdUJOeQ6htZVs0t06vJZ7THaff0IumM+qf0BFGfUZlybOqGuug7iu60bHnhyDpKspKKMuKjELVMp2LPM5KW33BrcvLYQ+pbrlvrJ/TtcmZH3O/Ar7p3Gu7Z7m3cxe0bDm2eVwX6pP7oJ0SvUucNPFEfeSnJAQ5Np4q0801eFfyJaZhvGaz/Gy2FyNhPvPp8rzcI2JsikAzajHLeChjCg7+inkJZ1IdCbfFTOZupSkH3EvmPqWfo69rYoNlDT/WCBkzsTWLs0NcqQHcGneenfDY/piaft+cw/YtoBuU19BM0MwUGfeCqDfJqCBF1ohG+TGqeJGUuMNj5XZl20S6o1LKVMpqSgHCzGUoFxkeZcyui7UW2h1zO4SmuwmpGBtkX43eBr4xvTO7u9Z3sm8zX9/sGRTmIWWW5ymEk8B2o520JIF9fzDUfWaleo3OwGCDijrVN5U1JhzEG1i5frObkNpBwCfzlGzD6DXNp5sxWvVfv1tUavEIZCnLONEimHASmDENxSTwJuBqGa5FPGduHUm2he8npOkjFHt22Z4UpiXMY+8wXM4bbUdb9tfsVllYqdGGxi5q42MN3JWsZhPc9VVr6izrP59jEY4j2PeY3gyxDoltFtsFNaeqTp0d39vr9qWLaevIr8jxEJ0kwh4KMswoPkOSbYsUDnpdyOEmrBrCKSmCqnHLxkbrsi8JIEf2mGSlYxoPZlOPhV+gjShrrZwVhRfFoRXDaRZ4t2lum15nJE9Kb+9fA75nq89cH177t6dfVD88fCEzhVJGjZR9p5dnIx00KM16esutT0rfkp0lWefGI+nrpvXrFvDpu9MeTstbrAj7txpBg/33e6b2dG+IxDCLYe31WoV5nYn79Fzwm087orzE5/7rLX+DxjEY02QLI/Oqw5iBcHhblTAoyHGuk1wu2K/pp+dnrM0CGjc4znBcZDlXs7jktcFTko+NsjXoWAFK2iMrdddV9KddOPgjvSFEuAdk7ya+uD+/sJmpI9PnaPZSHUvPOpEoZfuszpltNtvwtgittVxDuOe+scJp5zNOqe2VcdBc27vbk2mfIK/lnxvfkNMlojknKCHCDsQVSCYiJArYsqvaTf3gbuggQ+YMAtIhGan/XAzD1qgOhjEdQDp8CXdg/k6OTzTAMxZhz5jmZVGgT+gdkabLH6sUK2tkSfBZv/G6KJg8Sbrnv7avrmSGN1Iczj763cd+0n0v3bUByOqk8JdT4xvGZXgTKdJwtxB2ICjqFp8HtfYT72rr8lyu2VxDdfTVNpBfEqJRIgPTnIgWEp4CPcMSyo1p1wUPxnEf0rqIGZihpkVh5pCa/lbLZs6DOXM0eWfsFNKdcWWJapKFKU3cZ0fIupTWLA6HR194hjeurx8OCW3jZ0lXEV72iTbeWyO9/KK3RPOY3WqQ6vqrCXA2nep48PH+0egGgqpHL3XEu0rYoDnJMEdCcDVrQ9/+bY/d9ttC+cunnd9yRiX6b6EhqioCszrV69jOEXjBoLUjr6Zya8fULtVtoDO8S2Zfqzdnd+F34jaGmP1C7653jiMoVqClzmMNC3Se4QrrBfIz+HtQYJ9uP4Uej8kTj7Qld2Nq7Ynu2tdrmjf8ykP76Ha1gCyuKTjBP4lMRUJoIRGW+HCcsSHgikhNHEsTMX09EV7UlDZYUW6+kplGmTJ7rvza+/zJpQeiedplJWg1osFfxmDdncL6Wa2LDn8s7HH8C/ALN+ubuHsq986n4DsZTGHeWrO5ZnPuG25zexwzwnzSHpnfB3fD+kpPfkPpeABnmoi6MRn5TUcpCf237R9IPjXK5LBnPYLkJ0rmrlpMTMepYbukbVJrPM65MitqBZBlQgZ8jVbhi35g67LVUdiTpQdRt4P4Ou6OSC3wS0/zLr4H52bvxe7L41mBJiGHZiazwE+exBwdBpo3xGlWdJc2ujXCC7hYIHJ/JIHFm0UaxdQfX2R4GL5gTJucMepTkVuifny4uBhcCTdzW0RMkR4iB2OsdJmVvzR+JKnjPOR0FGXECC7mKhv/XEHCrwpHz3Kf0Hxk+QKf2h7bmWbSIeB5/0PoHM7xunuSNONmDT3WQBpTqjUg18BsA7U1mJR/nfJaNDtJrSc87tT4o6ePLvo9wDdmBIcfa08va49Qa5fdN3Y3Pmzl5AB8HbqWcJiDDPVypDCLfg1Z88HdAab95DuKBYJ4GUulDWYCf2pWiJxqfxpDKf+OtGRVLavJzYmWjmqby82RlnIbi80NQlco9v24bvz0wYy0tKo0EEIVcSv3LXL7AU7HpCyi9XqTxzMkzyA0l7TCuILlbE9ZGPOyRKVUGjMtdW6pPqp9itA7E298v3E+fy2pNnjtSrQ2l4ZO0AxxYPSIOksr9llrcoN0dRrWcKK7LKmDGHeCnD43XSJs3ghhxnJpikV/+oYxHMZYav8q8oAm/Tw4mmpqBDNL8sxxuyPndpiO+op4y2JPIbbFuK7WvFQMuvbUwcnb5RC654cVD6/u1JxDtqcwQhKkC2DP+J3q2zM80w4N0AW9SFAM1CixGdf+nuPhpSQ4G6LNHdnWWZsjQ9qHaQFg8n1yDjm8/iBGf2mt+RdndlwxskAGNDGKQzXyfSiaoyXnDPbqrBhZNrOSRkhlrFhumXFHpn7Kho8z4MM6K5i1IHIn4xMOd5MdWC30yOzMPswMBZZWCtfK0k8Y1gu2V7lXTpzv5E04KE7AU71CW0PVFcHpmNJDjXd0kXRFQ5mgAmt1yUU5aUV0hApIfBrRsrq8ZVZGVPuU4uNcckpF8loFnCUM5yIec8l+3vK2btdr6Wvf5N6pSALvI9Nlhv11fkfROlQBN8KvBAyLhNbKSyMREScHZndpbDlstDVZ2BjD1BGJROA0uaSUQvT2W+BMXnU23ox93ZvQaUjiv+OhxlSD0jUX11QeU7p1rTM+LroxihwPNL+pyTwYXhCdE/RhYRcG6PIm0S9SW4E/v//kjEkxJQqxGkpxiMXG2x2ruwhqx8MeOHJ+uqXLF8oO3D8YK3o+dGUUHpdJ7U99XbB24leorhhqG1e3L8PMssN3nMYq993uw4IwbD/Dn9E7Mm+qPy/7PYm3jAJzikrP1894sJ/gffhzwVP1BCA6KvHPTzkxNQ1N6S3AFhdgRcSugoi9kFAQLvuaPwMnXPUR7P7ONmxspaw5tlgqCwhduX8WZtuorT+7dm5bIWy6112SeOFa/wz9oO5HWM3fIhgiJRydradLyCoCdH9Yvsz+pgulxBEdoZB6w52/ZnWRQJlLZiBvaxF8XiyMNHHYSI3OlTvT6oTqNqFidUnXLpY+uSxdcjjWUbobtzFhYrbNadzgONGyh2CYJff1VmtQY0+R8kdL9f3N3JMtXVN5SSoGhfAL18GbHg26Vc2HuhIV85lCbjvOn9Y1v7LqQ8csxGGQh0UPm5+HMeRqriLLzIPypkIfpzmTziUHR7PNAy//Y4nD3AbY2Ixq5Cg6WMaMG2RxEeNRoFvWeipd0hWl49JUVqhNIuO+VLnX9NILyPLyFOqq3xG2C23t0won3j7NfqL1cOsmWzsD9VXkS86Fh6NK1QPgVlboYXPtjNzuvd5DvBl94X/lxiHA9BFdfmf/8P7G4cd+9x7vvuq9334bcybO5EeezzKv9tAWUp1vEIzYdqTiVR8+4XTL166GPWH6KOgtyj3pfSgl7hwxvv+34ulQMiZKg8ys1/OhYum30yhM+NKYDgnTpmHrVjEBNETG76DEuQTiyCjQ4nsQ0UE1/fLMx+H9U/p4CRZ8jOfa9nBT73/dsYkhlYLPB64ICg8IYaiClwdmB9EUbOCgyYKZ
*/