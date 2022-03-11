//---------------------------------------------------------------------------//
// Copyright (c) 2014 Roshan <thisisroshansmail@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_RANDOM_DISCRETE_DISTRIBUTION_HPP
#define BOOST_COMPUTE_RANDOM_DISCRETE_DISTRIBUTION_HPP

#include <numeric>

#include <boost/config.hpp>
#include <boost/type_traits.hpp>
#include <boost/static_assert.hpp>

#include <boost/compute/command_queue.hpp>
#include <boost/compute/function.hpp>
#include <boost/compute/algorithm/accumulate.hpp>
#include <boost/compute/algorithm/copy.hpp>
#include <boost/compute/algorithm/transform.hpp>
#include <boost/compute/detail/literal.hpp>
#include <boost/compute/types/fundamental.hpp>

namespace boost {
namespace compute {

/// \class discrete_distribution
/// \brief Produces random integers on the interval [0, n), where
/// probability of each integer is given by the weight of the ith
/// integer divided by the sum of all weights.
///
/// The following example shows how to setup a discrete distribution to
/// produce 0 and 1 with equal probability
///
/// \snippet test/test_discrete_distribution.cpp generate
///
template<class IntType = uint_>
class discrete_distribution
{
public:
    typedef IntType result_type;

    /// Creates a new discrete distribution with a single weight p = { 1 }.
    /// This distribution produces only zeroes.
    discrete_distribution()
        : m_probabilities(1, double(1)),
          m_scanned_probabilities(1, double(1))
    {

    }

    /// Creates a new discrete distribution with weights given by
    /// the range [\p first, \p last).
    template<class InputIterator>
    discrete_distribution(InputIterator first, InputIterator last)
        : m_probabilities(first, last),
          m_scanned_probabilities(std::distance(first, last))
    {
        if(first != last) {
            // after this m_scanned_probabilities.back() is a sum of all
            // weights from the range [first, last)
            std::partial_sum(first, last, m_scanned_probabilities.begin());

            std::vector<double>::iterator i = m_probabilities.begin();
            std::vector<double>::iterator j = m_scanned_probabilities.begin();
            for(; i != m_probabilities.end(); ++i, ++j)
            {
                // dividing each weight by sum of all weights to
                // get probabilities
                *i = *i / m_scanned_probabilities.back();
                // dividing each partial sum of weights by sum of
                // all weights to get partial sums of probabilities
                *j = *j / m_scanned_probabilities.back();
            }
        }
        else {
            m_probabilities.push_back(double(1));
            m_scanned_probabilities.push_back(double(1));
        }
    }

    /// Destroys the discrete_distribution object.
    ~discrete_distribution()
    {
    }

    /// Returns the probabilities
    ::std::vector<double> probabilities() const
    {
        return m_probabilities;
    }

    /// Returns the minimum potentially generated value.
    result_type min BOOST_PREVENT_MACRO_SUBSTITUTION () const
    {
        return result_type(0);
    }

    /// Returns the maximum potentially generated value.
    result_type max BOOST_PREVENT_MACRO_SUBSTITUTION () const
    {
        size_t type_max = static_cast<size_t>(
            (std::numeric_limits<result_type>::max)()
        );
        if(m_probabilities.size() - 1 > type_max) {
            return (std::numeric_limits<result_type>::max)();
        }
        return static_cast<result_type>(m_probabilities.size() - 1);
    }

    /// Generates uniformly distributed integers and stores
    /// them to the range [\p first, \p last).
    template<class OutputIterator, class Generator>
    void generate(OutputIterator first,
                  OutputIterator last,
                  Generator &generator,
                  command_queue &queue)
    {
        std::string source = "inline IntType scale_random(uint x)\n";

        source = source +
            "{\n" +
            "float rno = convert_float(x) / UINT_MAX;\n";
        for(size_t i = 0; i < m_scanned_probabilities.size() - 1; i++)
        {
            source = source +
                "if(rno <= " + detail::make_literal<float>(m_scanned_probabilities[i]) + ")\n" +
                "   return " + detail::make_literal(i) + ";\n";
        }

        source = source +
            "return " + detail::make_literal(m_scanned_probabilities.size() - 1) + ";\n" +
            "}\n";

        BOOST_COMPUTE_FUNCTION(IntType, scale_random, (const uint_ x), {});

        scale_random.set_source(source);
        scale_random.define("IntType", type_name<IntType>());

        generator.generate(first, last, scale_random, queue);
    }

private:
    ::std::vector<double> m_probabilities;
    ::std::vector<double> m_scanned_probabilities;

    BOOST_STATIC_ASSERT_MSG(
        boost::is_integral<IntType>::value,
        "Template argument must be integral"
    );
};

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_RANDOM_UNIFORM_INT_DISTRIBUTION_HPP

/* discrete_distribution.hpp
SYv75g7MYw4AeGIpuDLUztA9XhAEISMaz7xL2JOSn1OZv2/DOaDSxcTGX406pxhksoNktuOg1v2xk7yNl7IdkuVA21X5lqmrgGwUQKwsJttFn2sjWjAyWNH9d1T1mTUREyHE+/69DAIAEee29tBL88+7I9Vfh7PY1K8mSlKK/TZB/X1Jit8T16pc/ryqPJBXNZpXKo23KnRfMY+3KqWqqqGq4qtHZcJ+Oc5s9VQV6dD+xw2PqrH9yr6q2huPapw/nx48al941BPzNXzi/bzP20j39BPZn0bePygOvjpBvhqvfRQHD2CCiMsGRtieoJwEBSR0g6RViA5iDLVV+DNmJzjojPVfg/nNzI+xAIoZJUApD22IatjIb0mDzGd2y6R7KtxNytjf6rY+EBJzJco1IFNFFz0aI80OXoFBuCu69YBQMsoqpA+/Ud1whubgiTDZ6tb71eAa5J5ys/6f5k+eLep8LZLVTR2eny3+1H+tGenjb5rjH145qP1X0zjlObHDPwb6O0L2d9zw6VTLwdRNTZ3o32nZ2tFuz0neZzOGf6uVZ9jaXld51eoGC/z0qJ3vg8xH1s4nPPv14u+v/NqfVc8Wp4YWvv6d7/67yKq9NPV3aeHZ8lfVBdbKHVVKrh3bPcaeNXwcWwYk/UHMhgmVQO5sjN5rP5Z3T7LBvD0lFMFoYdYfQLcfiBo7vFDs7rPwXWVI2TqTEl9SdNc+GO+k90lTNNhYiZIBxH2FbiobVYT94L2qRAKmDDB5Oog0NhHDozGIVN3Qgb+njipRmeTM8v6zlZNnp8qHK6KHZ8Sqq7KHbIPPLjb+XjgIqbofXj73vgoVWlAXOn90eB34+azk83m+962p988G77uqQyQcwzEvxMZoX4Tigs4LPbzfvzj5jLVRfsARBp4d3pMJAxI/A7h8gGJHQJIj8KE3RO4IZCQMwn5+IFYFP60DutaBvOuQ/j6wqDqIrTCuWR2uijDssQ/+F2H8/4z/r4UJCuseqMABLjH5IwC8XDR5LpLkaRrFlTCpHBBPGsiyhO3m4K9HLCmT03cLIOs5VEUoVUQoPiiRXcWQ04jgMdRT04vQMB9TRYngZXVRdYJpPYG0uWha73raHCBD5w8S73pyczRjYwyUUAmnjgw6LwKcr9eePxYwj2GCY2gZTmhnlFmFGqAIUWhBF5uGKOtjUXZvqJm5KNTuxNRTlNr+hNAphl1HlHUYEsB5hO9YR/S2Dpoq/GKsjmBYmLBRFK/zOV9/A2/hCcHH50SfTwSmhXlPTwQ3Rfn/nAgR+AmQ+wmC/URun4vSn/L3H4nwnRI8xeC7YejmASCnRnonP0muLkY3gISlmORTMSk2tFSsn4StmJS3mFShn3S1mMyXU6lO7Kk0G0Au6FT+o5/CaqPMbqP0Zz+Zb42PwE3yH04V+8Ue0YvLL/ohb0+VTxuRzOIq1OIK5P7KZuLKl43Kh34q3k1qT8XV/cTYEEgW9i4ytDWw1N+YJxpU1PWzTDyaCsDhFs3pBuK46tLiH9RCKes9/U/7eWZ/dKZ7K64PbtYbP3s8ftbkBkJV+0PFMfTB3YxF4tGm52S53fTGzUadXfRWXRC3aGZEN4VuNFdwN1mwMo/VOVkNxuK1sgS9v0T/OT43cN4ZoE8AsMH629z621w2225K2P45s8UGALmVZP8A2RjAbGszlow/pJeUrHTEVeXENYzOkK7+qor+GolnTmFYcRejCw3XQGfbM+fH4u46Fy6vA139Aj0+tDh/u3B/evF0ONAzU1KzOvDp9MWzHxdefy5kbD1eF3j8OhKCOsX4uirD4tDkqkBKp244w6Uf/Rf28C5CFIYQ1k3oFBToeBloexlAEENyhfbjuvRNRPuxXfrSB/l/+BLy5ctzjS65OEyoohTeHYje/ziEAASFdXMsxQjCuilH0NAm1WLBWcBROmuiKLtQK/fjhgA/0jg/tQAzqbjHrQHjGLhwMANQKjEoOIDicxUhREc8QRg5+Dd/QHGN6E8u3sd7UPdILoPvAaDIEzFpliyO45tH5LsmnUKemPIhWKRGudP8IJngR8QZlieFQEUQCV8t6KKQf25EqD/IOYm49tK9Uq21a9OFKL2lLE6MksmzjH/jjzuCB+mtkhY8I+jtBvHDcH01k2Ugr8CMVQutNL/+XqVfSqdUD/jsXWes/hNvC4FXXA3srChKh1C3/dLtiVkdadUlHDt535rPaK9iIKs7EJLn+rX8Kc5LmsOMNaK3m+lvv0F6OWestYheds5Xz8QNnsn4pnkGTQClsoJT8jSTIbidS17lfweyOlX5CQEl/QavcdVYcj0Hib+VHK6UC8k1DmtS90EgvqlVh+8TBXOdmjIA9boC/F1s4xQNUnKtid96Jmxi4P3xpm2IiNtIt1ReQuI0oNyXfuxkcYrc95+3rRoezbf6Q5XD4v/gX2aUefy/fSeR7/ow/GPr27kE9PnSbJ23XC72R7tQfCulfK/ZXYAPvNsvwcmN5uW3PKgb5odl+0CmfJ7TnYtmX9sPVQH0XYJRfFOO/Eh/+Et+WwP+w7rTNUP0TxKkrG54+MDjXmu1ryMkCpP9fSfvZQ0HUmTaw3Vr7saxRN1YzPqA/qTZ99kgLT03mmkxmZ7Gu/rH17OJ3+c1dOcs01ePiGIa25F3N/Nfvi++1YG73c99/o5ENpD5f/va+X3lMGLw7Y8xsXvF4BooCgmFIYFN8qtcHRtRydIOmKmPN4qIK1qKSBzEw4bto53xJCdPrNn04w6AE4bQqWMv8yH27FbRivsDXwO9M1Ihu+NP56PAJpjQOyVOikggCtPxo+Pf4cPgYxediv8U+SOoLqybXXPl9NEJl2KnWfmQZ/wRbkrqk7aTx4rn5PGizT1riw9HKrfHZp2XUVHIvrjTqMiSH2RXhYo3GsSnJKoXUZGcpYp3/Z2qtZ3ItCgc9pvqgc4HLuw5uEcxmorbGJ4VHYOMJ3h7/7QV7qCaTM5j2hRM6qieTi8TeHZF6qSZzab1SjyEzFn7Jd+TFv9rMpeRl0pucwXBlWtdcdhWKGnFULFusUoylUQohbthmc4byYAbiqpBZgl3fXY34TF9LzJc1fMbSqyneb3j4CuJMKpnky5Gz7R73OHFmFrSqLLmMGpvm+9h1xfnBAEYQIsJmw1llsk/295UWqnAO5rnTmXRuOJG29PPxlrlOYIu7mj93SY/9BsSM2z1d84QEHm/16EL9PzV6P4zYzntRHkEf3Vf15M+2Gf9RzK1WcptsXJRjR/rjidDqP/v6UozEov6L0//LLYFXT688/6ZvNR6HvhAFx56/ufXl6Bf/CEurRSalZH/mKIi72/PubxpsIVfmrjRMbWRCKjCA4VVVhfOMxXBjoQxVAUVvoubHQ6B3RMBJVyFO3gP/DaG5MsfAMUeGRE3AkBl38qjTk3qXJDdR/chBlVETp2/iSWzsvo18Yg+nuHFAKtBt0DdH+7uNeZCuzcwCrayghdDvIyhmhrxeRQwKrOaO7IRYddwLu1jXln1EfFZKyMlk5VBzUwL/qEXo7J/241aZvmroOQEY1mNLPKIGJJxZSIFY9EqwSq1XjGH610DVY53uYa9FQvpfKC+IoxB9EgNxQxKjeiPoS5blRqJoob1y1nTN7yzxkkZycbFmooBlD+tAhgHud6exQ0QpfRUe/50SFcILDHnUp42iu9ZBPxyK5MwfZIsnOW34NlcJvkBOTMBjn7WyyhlrCbwtTSXMIrt9XLgn7iXwkmCv3LRAcvfqVd5KdOlWA1ftJY+ijcffL0WEx/3BWuhPvFnai2BkbjeLJJloy/9p2w4zWbacXWgA4Sw/fFmlpp+5mZ8qxLATgGX6c32q0q+JyyGoLZSG8Hv/rS7BdFi1HJEM9Anu0XxVET2X/aag/ZKX0Z62mbcQ4OLX75+n+/RkfJqYBNB+yn/z6e/KXmbOUY6fx0+jz6S483bHsr3bFqOvOVpDlF+Q/FyvYPeu2Tr1RuX+JYx+iOMwcabEoooQcujHsrVPY+QTJzQ4wGOzxXuKe+JzRGVXKsFp5zr75KevZVjfudXx0O2+KhHy1bBu+3xg3nAnHPQYsDXv+8ZL79dvm/biXoYY7z6hNc56EqQRcx0XUlv67ZCmfmYKbSYr3APe1LxodPmZrz+Yf7ybT2WyXW6X8XOc6BLUXFrwV6j8D776eMnaxfbUcGXHWqFzFHhiUHVV7un2CjL4c3RTQdcJNhwmJPMUvN8IwiJq62DxsezvmQy73JLfsxa8fQtVGagNrVdMICRovjTitkXnAx4fEmV7WHka2VqJo8oUpGC45FLZfoFnhgg6xpRiHnFb6246Dd/1uE/c39E6dbFqxqXvBSmISWa80k2EH9xo8ytxmdYGffl2wYVSQJpR/1EmBUFW8/CVOOPdNJ01iH7Uw9TjHhHvYLiwc9O4UuS0S7STPppG9Usmj75B5GM9wT011UwTRWck9hiv00WWp53/O/rsrMfmsbw73c0tGwapEVyzbBFSVqPF1zS5e62uBPZNJIgkxmlxs7P0ub7TTqeS+odmF9T4elYyiak0LdvCyqdarKckOVlF2/dxzzR1XlZ71NQUyby5skrlOznnNHc8ie6bUhZC+/8X7o6fG2vVZ9FGvE3iNOyBODp+2VwvJ6U35V9vTFs3ED+3veU9ZCX9nEYr1rOiNGOwnVyrmtLfSFw1hL0LlBPE5+iWOwXm6rVG1Rig2oBfsiGKLOFQZ89JG67aU89JN5gkTH3A8v2gDAPt2GOB3th+69drScp2VE3n8tEKDUlHF0mbIcoPopZ7ynT5RsVqvs/azr7jXLNJ31OJsEJBP7/iESJoyn9gMzEtnbdSBnasRjS/39EouwvDTbaaWQi1Lpj1FIwZUjusP8zEqW5yiRZURGHdOAZ5WA01+f/HYniNl1lXX26O1ekkkynNtTyvyJRloe/HHbVYGNCBa6Falb/G4liM9Iq4vgl+ktCmuUAACz/05mbYX+e2NOVkbZG1zQ0NEoi5Lrx93SFUbWNHpXoUvHL3w3v9b61/F1srY+h0Jv3+beKiSVg/jTf7FT8XIDcdqy97XRXX4WZmbBF/OzPfOPT1ZUJabMhv1o/LPPjjvaQpak2Q66Iju+3l0ciYYWEcuF3t1enf6TePtq66d74y7WGhlDRTIcP9FIVRRNK7q3F4p//nHUDrLDTxtG4VKx7wvp60yOolC8m4nGsNTcSuMsH1pKNnNU24kCUKine/O/2XiVZLMOA8jC0+ES69/IVWxayym0rO/0ZVEfDOpmChqcXAsQXxLLnpCHZoCxpuUprU85w32tzXaUizHMORiz6BQW3aWQTB7ehLG2cmXf0ix1NlTItMn4fqs1Zxd61KVcRA0HasnzHEneufAhqDaSttZ6clZXdprlVpoT/e+7RZ+PTFKAKWaVrWR4onk0lkLVyv8pJwkIdB4HC2g0qst+dDlN11R0T4DXiG3crGtw1qil35R4RKOkv0fVScUgfZzaCDVj4lZqVb8c/g2Te1iBH6IyVKboeHJMb2cVv/yoa5/2B4LV71XviHYo/xcOTzEVC+bvvNl+aBZZrG7Fvt0/9xoA6QUqd2Cajuo+gQ8cJ+c93jkem+NR3mQSWLAgfiQ2G03E5qNTI/gC7BmVPHuTOTw2KMIfrgrDhWRhcLAbVaKGxx4YaKw6HDyFEsEuNE8wYlD+oMvwomsOl5ziBBYJuSBGuTkuuU4V3dmf2Iwjkx/uh3xBwRZaw0Nj3gcoYYQiIBeND8EAGAf76vPWjRSlb+E6bHScYu0AMAvsuuA/G/V8EVPKKZX8AgENLnf11TBzvGz/8rgGLL+6wuBS34ixWXIsVd3cohZbC4u7uTqFFW0ppiywOLe7uBUpx930+3+f5neTk5CQnOf9MMslkJpnMfd3X+57Mayg8SBIYWHvYOR2NrYDcXSf8KZMYE21pf8ToTseICt4c3RKV0k6ocZW22b4AetoRiyzWDvC8TC3vrtD6gHlDo9r1hqb+/kjAm2RSlhSuh/jd9SDkOyyTXqQ2rOZcn7pTrLz2XaY0RQfAim9nE1rYjdw8nml4+VEHF8MWdX+7l9+XyN8ovN93wkuj/WWylMNy9gw/tD6Eo/RNMFJGilkOR/gUG4fDDoBGwF8EAz6ExUA0YHa6RTiCP8/aefkpC/TvRAe7woVTQM+Yi7Yh8rL3nJVkxF1rCJOu7yPuR46I6lC8d//PqxEJAITLzTv2nwgC5qhiBUJjIXodYN5MI2JWQsEoVgaRbaz7cZp1s7kuLhNd9homBDfHSetmF17g5SdLA5PqLyG0cCx0tTzfUyh+6MEmw+gNFtc2B1hfbD0pYFmOng4ebtorB8AvQVEFoyBsDwpkGhnEuWzCVclW/NDOeRQMy6pXTW+Ssf6n+SDidZ/WWx/2Wx+GB6aBNuI4IrZJ342xJ4EYd2gvKboaKDQrhkezKI/VksPMQHdCaEEQQZsJx8IdlMPFGgeRVQNAgvTrUF7hDQDDXgHrZknkARHSxROkIT9NLmDq/BJ+TBkDoprE8/BIYEDmQzMuvo7Kvj8rPAlSuedYxzDuO46v0mdUSoKjMUmfmEnR07QILOJEC0VbSlBTJKJAQJnqZjIb0xtF8CSHazIoANQJQCHyGsX/Bgo7l3LIUYmeYs8EeqqtuTKBpUFxOB3dQQTihsTMcqJRE2CQqjAUvDU0VdQBsQRh0/82E+3OZT3OgGxYKst6AYTyUrGubwb4P3rFhCj2UIOaKnlIuWAWb2fg3F7VYGPABPSglqnkX7FyMkyTXZjntW56Wi69Uy8zFz/0gIOSXf2CELItYvecH+t5nDUB3s40I/dZDbL5lrxOalI5MXHYVjNDrkR/XznTndtWSPLVsFr/5/zHWgfG3wsagbNNVa8rnCQ/mUxbtHxN0zxkNqcxWUSn+X/9nMjtxLjEakYaDkhiBmxD5b/w+zdHop3C9TGIE8WZ0svMM/cQbB+VY6584K+ddoRN5sUp3r5h4tnulWXjCgdHgJB3W8vCrXBcrGkUCB6jAAx3SvHGqaC65TDGemoCdvEMA2Jr65xV/eZZyE/hsgHcro40S3OCAd8y+urCX0suQpdmu/Hr3aM8321MeVD2wK68YqwlN7GMjHvZ2bzjNNuscL61NpNENUWpH9jMZ6roh3SdJrofkNBd5wxAvk9XBNHaMUWrBcm+8EkNDdp+yfNqSPNpJ72Q1j4FFUaTULbLEcgvVB4lQFaEa04CQoHNFm1qt1M4xP0bHWIlkOic5gBMipsBcf6GS9+Jti9F0tEJ1gc2FMj5Ph7dJly6A/koSf4uYBIgXB+Fwl7IQRHvIEDMTz0oxYqKqrWNyZTAxSk6LyAEVoLD1IWthRAckNx3GepZNIKXGHNm+kLsTcby9L+R+yTlurlyGok3tV69bigUs7fGyp/vpBdsSMZ3Mz9unR02FG0uLNw2u9/7FdGVlg4NOwzzy19aoh/81kfn4e6Yz/LnxfX3AXcPzw/5K/v+1z/WNI8Dl0xXbzCv2y8LPX2Ol9YePb4hqhVhZjl/GY6+OPL7pIRDAHIO/CrIif1soZYWEJLBqQ+rFQaw25ksha9VDuSGJlosbwFeoL+I7QrSjxDOi2+tt7YOX3p7x38z27qcEssR1wXT5SzkvCFlK9D11kDwg6mFa/vwqhBhljnYFPpxlwOYiLU7nFN49B/XPMwlLenCmLjs4Nfym1HxQURSjPpq9/LTwf4Rje8P0To/5VdlrluX2o98lH+uLAXDfvyTPvZYk1wGrr3p2no8ClEOWsf2hHXyWZxGOgbJ0TbMf4EffIMMtu24AnGl1svI88aCeCAYuOPRRYCKGzmx8MG7kIKNy/rk9zPxNsARU9TFh7H2I1dtpElr/aUcyyYVqXH8PG7EZUOn/AzG55cnZJDQVxSDAJfTu30wmiEbpnj4jdBs+k3x1cobWvQhj1WsJbzzrj85BevZWHAA08Gjsx7Lw+7aj5CcLeMtxZInVvmQO0mWKUw2rWw2GIQfou6FfZiNxKmmqm8innAkyTNUlZGDJZYByRuRlDmhL84IPsJhnajQWNLn9Towx0bI7w+hHDlhhJvkkpkwxxQgSAfY+CFM2Dg8vpKTW/51iDAw0TZc5iZ8e0NCKcwNbQX0LsEmQykhWiM0OGjvjWDYbHaKTkAMZITafIRxTuQwYyR4g0yfMtwoR85ELMrOmMbG8b/TYoJQ4QbZih7GUV6U0YVEobjemKH84T450W8HqQjFkNessFRUEGRD651xTFQ1BZ0eAymcJno+JgmdQ/HYpAXZEEg2js2qJj/XhSV2x2TPxxapkD16wzJuYiuM4zRTY0lbY3Bt4mrn47A+06CuCMv34pqN43lD48BNsZ+c4tvm44mI4jAF4jvEEnpjjLN8YD+ME361JvzaMYYyJgxTJvbFxEOq4yYDEqeg8djAxPn5xHqVRKhj4qpY0lp14phK0t5g3HpOwt/5pEJoAkZX4pFYcmRr0qZK8o1x8g5H3O188jun5IK9ZFBN5IlYLDgwxRaa8jMmBS83rMkY9nc6hdg5/AMxREuQOFEPB1c8lXYoeM0udbcfSieeRm2cSkGVRK2axlWDZMj1YPqexl9jzMbJSfU9VSAwnQY9ncYYmy51qyp0SyaykC7vrCTxCsYnnqESKyMbm0qakqZ6m/HzZQbEO0PnVSbLlwwO53TD75mUTJlguUwzqizOsEw5ziyHWCYLTphVYJbbAtxuIcNkIcsHm8H5ltBVPDsgl8Hzb4Yo0D3wNlt1UxHunCFubTti6PqCLQrpnLk7y9RvnTqtm1XibVJpk0M3gUCvc76LdB124Mr67BY/FN/hK/jXCPb1G4wiJkHOPu9Dbh5mah4mC4zCCcghB8TczqPIEaz/C2vmzMe0yw9rfk8OKGipwSSF4XIwciCJJfmI4k2tAW9FYP6boAYUAdSKfQBOwJhOKL1JNJBiWWSIf4su0dxJESlmEy19FacbRmwJAKSl4HWdAMVPgITK4jnnxKK2wreBxSTWxQNgbxFf4TtOb2VmIcEpew0hoPYXCXbWQqEN0NstgYFGfnAPIU0KF+mdSCMbbJyTn9eK4JZflOKOYCYl98GKgAfFT8MvWUSMrXuBQ5BelElJ7b/JhaNsxlLhLRotNJnuWLglJCMBlYLhsfATDKXhnVAwo1P4eFOtCO4IgVcpPHJKdNTluIyVgmo=
*/