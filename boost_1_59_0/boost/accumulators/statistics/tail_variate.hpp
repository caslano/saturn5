///////////////////////////////////////////////////////////////////////////////
// tail_variate.hpp
//
//  Copyright 2005 Eric Niebler, Michael Gauckler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_STAT_STATISTICS_TAIL_VARIATE_HPP_EAN_28_10_2005
#define BOOST_STAT_STATISTICS_TAIL_VARIATE_HPP_EAN_28_10_2005

#include <boost/range.hpp>
#include <boost/mpl/always.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/iterator/reverse_iterator.hpp>
#include <boost/iterator/permutation_iterator.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/framework/depends_on.hpp>
#include <boost/accumulators/statistics_fwd.hpp>
#include <boost/accumulators/statistics/tail.hpp>
#include <boost/serialization/vector.hpp>

namespace boost { namespace accumulators
{

namespace impl
{
    ///////////////////////////////////////////////////////////////////////////////
    // tail_variate_impl
    template<typename VariateType, typename VariateTag, typename LeftRight>
    struct tail_variate_impl
      : accumulator_base
    {
        // for boost::result_of
        typedef
            typename detail::tail_range<
                typename std::vector<VariateType>::const_iterator
              , std::vector<std::size_t>::iterator
            >::type
        result_type;

        template<typename Args>
        tail_variate_impl(Args const &args)
          : variates(args[tag::tail<LeftRight>::cache_size], args[parameter::keyword<VariateTag>::get() | VariateType()])
        {
        }

        template<typename Args>
        void assign(Args const &args, std::size_t index)
        {
            this->variates[index] = args[parameter::keyword<VariateTag>::get()];
        }

        template<typename Args>
        result_type result(Args const &args) const
        {
            // getting the order result causes the indices vector to be sorted.
            extractor<tag::tail<LeftRight> > const some_tail = {};
            return this->do_result(some_tail(args));
        }

    private:
        template<typename TailRng>
        result_type do_result(TailRng const &rng) const
        {
            return detail::make_tail_range(
                this->variates.begin()
              , rng.end().base().base()   // the index iterator
              , rng.begin().base().base() // (begin and end reversed because these are reverse iterators)
            );
        }

        // make this accumulator serializeable
        template<class Archive>
        void serialize(Archive & ar, const unsigned int file_version)
        { 
            ar & variates;
        }

    private:
        std::vector<VariateType> variates;
    };

} // namespace impl

///////////////////////////////////////////////////////////////////////////////
// tag::tail_variate<>
//
namespace tag
{
    template<typename VariateType, typename VariateTag, typename LeftRight>
    struct tail_variate
      : depends_on<tail<LeftRight> >
    {
        /// INTERNAL ONLY
        ///
        typedef mpl::always<accumulators::impl::tail_variate_impl<VariateType, VariateTag, LeftRight> > impl;
    };

    struct abstract_tail_variate
      : depends_on<>
    {
    };

    template<typename LeftRight>
    struct tail_weights
      : depends_on<tail<LeftRight> >
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::tail_variate_impl<mpl::_2, tag::weight, LeftRight> impl;
    };

    struct abstract_tail_weights
      : depends_on<>
    {
    };
}

///////////////////////////////////////////////////////////////////////////////
// extract::tail_variate
// extract::tail_weights
//
namespace extract
{
    extractor<tag::abstract_tail_variate> const tail_variate = {};
    extractor<tag::abstract_tail_weights> const tail_weights = {};

    BOOST_ACCUMULATORS_IGNORE_GLOBAL(tail_variate)
    BOOST_ACCUMULATORS_IGNORE_GLOBAL(tail_weights)
}

using extract::tail_variate;
using extract::tail_weights;

template<typename VariateType, typename VariateTag, typename LeftRight>
struct feature_of<tag::tail_variate<VariateType, VariateTag, LeftRight> >
  : feature_of<tag::abstract_tail_variate>
{
};

template<typename LeftRight>
struct feature_of<tag::tail_weights<LeftRight> >
{
    typedef tag::abstract_tail_weights type;
};

}} // namespace boost::accumulators

#endif

/* tail_variate.hpp
IDZYfXx9RcgXeL53iE96QDwCeCsvLy0tfzpGmWoZ4NFik6KiYF57AJ//2H9xMUR94MWa8U7v9G0j7vLgwsLKQSjDc8RqBWpEJokEKiQKKMYHJGVkaWnGRupEZoCNDvUNDAxPDxD0ExH0U4xNDY+N9031UdBAfCN9lcwy0cz2AEtpAPLydv/h5d0L4HEDAD/lAADp5AYA0oMG8EuF8OU9B+PFRwPAX8UDhMdO+kFuHh4emn7GC9QwAIuvu/sEtpYaH9te2oOwekTqHCR8kSgczz82NDy5vAXRZbz7LIrPYQcF/Yl0/FA6+wEkZ1vp4W/H6caIGgIifDmKxRlRiI9aQXpoU+odcVAYfExdA8uzWDmh+YKnkGmXRuSJscRMmMJsIXucOTNdd3rmjRpunYi3+mvDyb7mz7VV+xIyXJCvS6ypEKcUHHVM8Tc4yS2pQg4RMX/TpxO2YUTX8BkoL2WYk+G2jQiyCER0sTReBPRLX6ZE1Fujl/Q6yo7Io+QibLYcRZouwah9cwnrdCZI52R5uwwv+6byPhptkk6mzktyi+QRqonnupwYOXX7zJQt70WZ+CMWqrCSZ28UKrI6orE4JsR340O4qWl0LYD8n4wd9hemob5WeXrqm55Cl3ISzurWZvcNn3J0bXeDQWvPW6yGDLDev8l3PnOQb4wcSlo8uS+Cn+t14BvDK9OhwxfKZrlcEUbtC3rW4i8yKnj+yUW7izNEGF/9g4hDbivltg8OY8GNGqPyPYV6M7xoq/rCSHHLOh2QhvGbEfz0pQlVdOtZo3b4YPJIyGbyyPTdEEMv25/tdC2te3LmzT6Lozi7oY8sJpKVOSRAahGytTv1tBu33PTZdwS7ATJ/g8B+tw3otr5b3/PjJjQ6cJ3lFTTnTwyeH7Y3Fu4BH6TV01O3ggJ/ssDB0IfTitSczDoF+cGxyoa7vZDhC++v/R/TQJzXxKhLtEzs18Qv1tWMSOqRmlVfH9C+hAVFFbk5Y3i7eqb6OJUPEXDck58/IDEXPpj+I9PPWK9ZOK9YoUFRIUJK26Nr7ys+bT8+gaZ5oLM/EHP8v3MU8o7kDooJeUxGGIOIw1kgwM/b9wlYDgYBChPgBxEhFC3RR6r/aBI5EXNDWfDdYwy9mHUsKO86wxTbV2K+ZMFL1m/5BV18aDRe7Kms1mVnxKBGISK5e9gxI81EpPCwhCmwak69fgLk0YQ/hYdy7z4kMPPE7RqnaVpE7z4zqyiZvkcn05LnluQjhrAqM19beTSGDbjiZ04vxmYJad5M8+O5b6h7ZEeZ7LytUhGkGdcN104knjWDiv1xDEWVg2pAbv09DyjipYaoItKDRY1HPcNoImim9Tis6C5Q0/sl7ITIA8yz1VYsYS98/cbLrxNxeOcmRh+LNNpthYqtEHfP4McwTG1s1BJV8fp5w8st+5OwKuAMm91DV/5DwEH4ORT9rSs6q2vh5+f+zgxC4QhA/Ip9DFfGkxeSuopPRGWfG1pPNJRDffZ+fUaL7QlSsUhWY3RRdKznQ3fQLMq8EWcSi8Hn9M/UoT6Tbia/LrNWdPVRtLeX16yU4yjqX0HjV29NrA+adwVR4EOnPT5pUYwCmM/KsCzbw+At0h/tfiOBdIHkwfHBpN1HYkZls4koQHNJuebrhxT3Fyq+WnLe4vvsYPXJt2mAbGbJjSVkYcg35cltColpCPbNuNh3F5K+jYlv/0HRZVoUBGENPE/XJSzCBaWFj095nrBgYl3B1XSFlR6ptGBh9KNSB3DM4ujoOhLCD5oD2jXdlKEkGhcBWUzhMb9usxSZxHu4RO4l5AqE5MKscHpHe+Oq+yhfWQecKBga6tuJ0x/iz+iogAOekdFsUspQHqLbXHz8vBxSSntHAOTV8dy8b1MDdF5Jcip7BFNIotkcmEvzz0ZnpMmktCqE4lMDXyJsdmL0pGqZ5PZz8kukWVPOHB4KRNO71oWaJbKif0ZIjMUlPrs+74Z0ZplZZhqC24x1T+9FwpUu5IPD3cHBZHb3V6YLppM/JIsVloymkzYCU+Da9V166BtHyTna0rUxabaG6dro8aH9wAC7c28tOG7T01t19qqF2dKJ94m9UsmNovmGWJKiG5+f5QTnSwtCuV9QxLs/S30nAPZfZFN0PwDWwUAc5KklcyVv7O8A6OTooTyTdOizh7wsRpIIIlSW4rHhpzlSuxxTXF4HfiZxsxHBH2zeH2HQPTSc2DdTgVQiUc4Y/iFdeAGStVI3Mv6ORy8PcthtFP137jD+ccuUHbrSzOsDWsoU2u6IB1c9cynxrWoLopf+ItYW3f76deZgntql0P7YgpUbTWs0MT41sQz7P8yCPErTcM6vbdLmOCVF4/oa263lDyITn/MutfSbnvM6HbRI2yE4hyiifwpZMAEmYZn/QXRqyWRS37Ls/NwKMWt1eBy4ZLIW/h1sfAOXndQS1FnpQedObg5wMbx7fy6IpW3UcfiKchq278SEzTQktctbWr9KkC66A4rzG14dRFIMU05ZXJGWxAqqeh0HfHUdl2vrMlDmIJftH79BqKI/oSDwgTHmAe2L2Fd2+bDUSw3UhpuTDta27lN+yQE1s0bvFKAPu6OkDkMRV74iw/FfC3UjHxKK5YX7oHww/PiZevhhnfnRfDD88QnWNPmYoZ/p4a3+8eDpoE/eroIF2O1ySAouOZ8HAXic6I6PIyFAB8LvFF/UBuvO9YbxXZuQf1OTP61pzzjYObd2I0JDY2TAuU04WpAo9Sl5KMqM5PzZpx7decd7pTUGi3FDEvBM9V8ZzsKrpKqaeLiaPBMGgrmPrDq0XJD4NArfBv7kT//9p0rJypKms4bv5qQUFO5mq3XP4k9UUWDHpiRgG1MtTLptPfUDADWbXhbCIiIinHwHgHnnrTqo5eC6nrb+UyYujTTdLVECSgUS+Afe20KhOerznn7f4476nSPw5PDzIvul6eN3bvJxk/eOwiskfgsoLNAz8L4zLf5v3/vxSBZ9MoRpjBuNM8qm2uBtN/oWBdZavu0i4cTkuRYemWjI/0b8vKbe8NMIgZSb7SRFK7TL2/8J7C5TOHgpHxy887k+lqMVCo4jucBqmd4aBw2NyT82RNxv6Z9PS1wczE897fNARoz9x/hrxOCfZcUj5smoW6b0M9BMrge72epDHRivHdUu666T8kNPkXeSaezUclHnxJmspAzZs6ZONVmwBssDdk1RN0G6zSFXd+FrxT2pOqu1O0QMov8LG4dj+2nO8cCyP2psvzJ7Dt7Z2fx8Bp+A2X1Gnhr82L6BVmbGxu4Yw6AHx8ffFdZyfL84ff48/2RFfaH1esOrntX0eltf+8Begt1/9iG6fu+vtLm6+voAPz/U2vvmaP8McUyysKFdfkMsuxU00PoBg+DNDowBbbHl6fIsmnHk9QsX8BLmDhDRdTpf9oU6W9peHrDY8f4MroHFjaFO4ADUfa2zIE2M6q4exzZ9HkzGhCThsV9PeAJEp0gkJOgoPfWOyFO3U3UWuUK289NjEqhsS/edxLf6SnqASLx8yIvs0EbusDYJncAAZCegElG5w06QQLX0s1rmS58PtKdvWOFdd9nsQWCLjpJVN8ZOinzJBLysfF4/CnpEUzOlNrB3HlVPCgqAHu2i8ZJUOYFZufJvz92ho+p3u3HeHShQXlQGaRJO7TDWaElcbxnOAARRNiqSQRqj6Sgi2tRUCoqoz5JGi6iBWAqRriyLCYqVn7Byc84wmPLcazKmaMfFSb8HP06798jk8sU4N7iwqaasKAp+/4t9Y3NWdhbZFLjWHm696ip8d+1iOwB7p4pTZunEaBpcUL/IuwJZshkrKDqchrb/uPlDlUSIcpvzJRoJUyyOCLelPCGT/5eYbakQT3bqKLKPFkR9vBiM70AWfOGm4N/8WDeKQQF46LSG9obvg7ZExn0QW3RueLnHxMEngNrCQrWNeS49x8Px/FNUTXZ5OyrdwPGVxFFKfSYUYyP0TfYNzKK2tqXQ9M1YdtD7+z5BMfG5lrbuUIa8DlzTB4RTYzLYNgYWZzeUqmj2Eq9oi2VghSbV8MoXHTVRk1CiyMr73FNR9nD8hYRWVOvXCRSjOdDZh3LFE3gHbSciYEf4RfEmSPhQGD5KWpdfo9RoOq8WPQemyyS4VcNi/hsaxpASDYxEzpLzHjVCxupylUoY4HIiHrry0VbnBGaoDGWtyPO2M4yD87+e5Txls/ZRRaTXWfA++XW7u8sr4Htx7i46q+AOMU77WHfstFeEgRh3pTf4bU7FS5gUZrS52Je+GwRFooSKoSTT04TCuGbNZm3J0lvRu8LlvzGmkbO43X8xz6mh7SHt9Dm8vD9IRdKLqkg05kYoeXXQ74vviuPOUXqYexJN8eTxEJfaj9qLJL2fHZ8b/6ptt1dr9lGqbyqBEElKDGUIQsraMzWdAzCQO1F4288mXBIN9Ab9DUlG3+N9KZ7E+MnsZ3CayAW9iOJh10yjG2+SW1m+Or5KTpzaulhu427Ma30jjTMapezRjF9f+GiAkebR66GpVb0To4roMce6AY1FYdho3aKo6/LwQsMRSM9UuEF3FEmEnhbN9ydtjzA5WLBLwRPAtJF1wHR8Tlug2cbXBbIqlX/ECbQMYW/d3UuYJqmV/lgjReChUqNRMFNQpPYN28nlUeI/AFQJyd9hPL8prT+2rd95jO9xdbGG0v4gjemfK8r/y/jwl7GFXC72OKwDJVTnOFznOAKKRTaHYNS6nBROdZYkkkIB/TC8ZUUuZ2/UWp0MznaO5HWeZJVSoXITLKyCrHuzkePiUhT3lS/FViaFt1yQIJH2mgzTzoSoJSyFU1YN8nKU8SkBsxNKtDM703sjjxgcjNTomI7kmM4ovM/wbrpOTfJIpR451J5h3+Lv/urhIjoireHv40eXxJowVFfWd8kFtYRRcJKhTN8CcOdsnxcI2+7/+ElY/onzDv5PTC1cVN08ktBIDVINiR1Szck2M5EqWxNaGuvPhSht3nhNBZBP7z/qHeJgmVtUQCPGeKkErFOwM1gMg8QTCRYozcAarcEaKSjHDOarHTdyxofZIorZonPSCSuyC25VkddLCYU8OZldWZlcWRl4BRleObL1CZT5cdT9MVT7MdT8MVSg0hWLsqiHoZtTRIB6xb1UcLd9LZh9ZEcIx/ogqvqgQmXaz4QefKZHAig4wgg4/ZMMzAW4bhZKORt24lW3b1RANVDhJ2bDqlCXfOT82m4i8jtQU4z/26cxC4AaqepNjBBJ8ZDmz7NnOW/8lMPX6l0pq0wuDErLvxGo89Juy2kCc4Mp+Vfx0lAtZovMZ5wWio8nLqsHPpMHpnrVt/rVtX7UtybX3ZxerBE5qiDK5GXr73qprdc+Ug0yXGZNruQ9KJ84ykkQ2TklWSOSD1wh5a5o1k9sSB8oG2y9WM+1nSSPE4z3t28Wr2aTRWu11ddneIjcN2SnE0dS25lvoB9rJ7y9wBlB81B1a90HHfddhJaZPSbH6DPQxrmKkIVNq8Xnzqv+8Z0ucNinETOVuNoQOWIWuRTM1ZvlzMsmNYTjlyjwWX/0Tu4Kug35ofJ0jgXSHu6wA3iStKgQ354zm1vPVissfoA9/13Bd/ODKZrTf5fgL0oL+ttCV1PUaRQiT7ORx6iWOIEcpj7UdBz2jAdT7jGo9yBcLhjEuHeJOvIQni6Jl9DEzSTF6DPj/cM/3bkdv86x7HdtoL9xt+jmm3oTjYhXp1SeelMsD1WnlLmqx8XVt9VyhlvYnBapa+az6hyKmlrBonDSHMvCG5c1R+G1NOHa04bQpf21O5QCRkqCEi7emptsyhWakf5IgnyeVr5xy40o0Pjafe8L16jOkgi1f8as59BKpoIHB9G6y32IEq21vUy3nmDckrealHF5Ej1KabQyP61fxQDiXdGMqgyufV5X0cbLSoZL1Jzs6yihhllbQJiNw02X07uakVRl51VGT+5Zc/lhaa7Y2lMmXcWuecE1GXpVdC2s9ExBtdInRfNY8KxNtmAbJi5QL+bVCfTUPaIRceP8yc7TPZeb5d3j34ZkFWO8Js315TllV3IFZjRr0XP1vfWRviIzytNtj3WleI55Ef3tN8oz5b3xHfkKew54cFf1IzqyPr52h7KOY+U0XEnRA46gpRNDH5tWHOKpNVYXq8GVIA0ogDBA2Nm8stCqneCH4YDshczK7MkBRItNu+8ws/xv/+8p8t3j2988gziRDBE/EauESpoFBi/QYfrlBtw3p3GnTYXcg4+K04reitGK44r9itWKZ9IlIfGeE+9Fb2g4QzhkuEPiU7HUsmKGskD7+6BjCmgjvGK6ZDT05sIGSBHF+gAALP/TksOXUdr4rkNdRBh4I/px+9UkQiN3skWqjKXUnmsujpSes2CjAkQDIuLYGLG4xTxN9F22iOYEQUpyNQOoxMz1uhHSwmsBVog/0wcbPQAoSNLDvpB0UF6zTOnNmZI9G5eBSo0M6HFWb5eBZy37U/1x372ivg+RKd0LTwbSrd3dD2M+XtP8T5u65CiMw7tQUDA2IvV+VPfSkyehdMDIfmquNdRXEJ41NrVhXc8WUXdMLpneM1Qh0StbSJMjij7E3lgLaynC62XdSXEbZSEJeqtvrnKjdt1UyqH23eqyo47d0Uqint1l6uS231Nt8OM8+QKZL5bH4+nnaStFn+6j9/GhCtap8GrK1uXwQyN1YvP40RuSPkHHCeMXGOWtB1EaZlFZFwZm1c+ZButFF60cZRCl7ZsmAbb3HAzacS9dcEFlm/2C/dpyBMOHHYmtCIhBvv/EQXM07UEORnO3ZbhMz3INTfVwxgTrVXSY6Al4CsVcju5LxQVWrAwM+nMLIzYFl59NUY5tD8oadl64a6IniTNgT+i8tgoLKWGw1BCV4on/KctRBkxaB/DCjQ2iheAoVpJ1ZltEpPiyLxsKg+ZtpYZBs1cSAWE5lpFhvGMq6xAzwavoEDL5CutQMYU2+IfLp9bHJ8sH9mWX86ZOZRfzBsoQAaZmvHjLOlj628R6WIYPJP4sddf8PaTEKmVyvUoOlfzHJ9yHxqT+YM/EB+e82AhYyq8/5EeM0w9Z6+5NkBbL6tJpVtv5wmQ2eSV5dV/fxePuDY0fg2OSNn+pGVfa6841u3DgpOsiu/T8Wg3l74iqFm2a5WHv7mDIX61e/Tofa/2p49MnziCteLGvzYwSGSym8HFITzqAgDNnAomAI9RQFvxjqYpJ8k+6S3YrvD57Uwm0GrqcqtKd0J+eTY+QGqnJ9x8Nkn/9KwZcciFnOpK1o/FzMUw37wY+nAX+PsCx7j1UCeSl66iUt6cbdMnz3ygu9mNXVbNSP/gkTmaz48FR/nBMyzG1JkzDMXa0EnPmdFYIDQp6c/3JA8aPj4DQbtAriPabQMigwbSA4Q+wZlWCsizdfCEDRwTyCnpuQvH00n92gnCFloj7PXU4lSmJFLmL9Y6Ad6SXWH98JFZZxZ0LDs8TuZHroHBzZNSZhoZD1phKmAJxdeMvIWJ8xs6dMgoNQKJSXpXs6TnNCN4VcvIUoGwRdPZOmYN53wn5/dB+RIjHJCjIqk8L6qUQP5vG+Pg/qRukvoAmu7GsPgeSBK8ur5NvYokr+HeOqrc37971nDrV3hw7ny/T72FXv5v2rI4w
*/