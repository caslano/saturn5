//  Boost string_algo library iter_find.hpp header file  ---------------------------//

//  Copyright Pavol Droba 2002-2003.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/ for updates, documentation, and revision history.

#ifndef BOOST_STRING_ITER_FIND_HPP
#define BOOST_STRING_ITER_FIND_HPP

#include <boost/algorithm/string/config.hpp>
#include <algorithm>
#include <iterator>
#include <boost/iterator/transform_iterator.hpp>

#include <boost/range/iterator_range_core.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator.hpp>
#include <boost/range/value_type.hpp>
#include <boost/range/as_literal.hpp>

#include <boost/algorithm/string/concept.hpp>
#include <boost/algorithm/string/find_iterator.hpp>
#include <boost/algorithm/string/detail/util.hpp>

/*! \file
    Defines generic split algorithms. Split algorithms can be 
    used to divide a sequence into several part according 
    to a given criteria. Result is given as a 'container 
    of containers' where elements are copies or references 
    to extracted parts.

    There are two algorithms provided. One iterates over matching
    substrings, the other one over the gaps between these matches.
*/

namespace boost {
    namespace algorithm {

//  iterate find ---------------------------------------------------//

        //! Iter find algorithm
        /*!
            This algorithm executes a given finder in iteration on the input,
            until the end of input is reached, or no match is found.
            Iteration is done using built-in find_iterator, so the real 
            searching is performed only when needed.
            In each iteration new match is found and added to the result.

            \param Result A 'container container' to contain the result of search.
                Both outer and inner container must have constructor taking a pair
                of iterators as an argument.
                Typical type of the result is 
                    \c std::vector<boost::iterator_range<iterator>>
                (each element of such a vector will container a range delimiting 
                a match).
            \param Input A container which will be searched.
            \param Finder A Finder object used for searching
            \return A reference to the result

            \note Prior content of the result will be overwritten.
        */
        template< 
            typename SequenceSequenceT,
            typename RangeT,
            typename FinderT >
        inline SequenceSequenceT&
        iter_find(
            SequenceSequenceT& Result,
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
            RangeT&& Input,
#else
            RangeT& Input,
#endif
            FinderT Finder )
        {
            BOOST_CONCEPT_ASSERT((
                FinderConcept<
                    FinderT,
                    BOOST_STRING_TYPENAME range_iterator<RangeT>::type>
                ));

            iterator_range<BOOST_STRING_TYPENAME range_iterator<RangeT>::type> lit_input(::boost::as_literal(Input));

            typedef BOOST_STRING_TYPENAME 
                range_iterator<RangeT>::type input_iterator_type;
            typedef find_iterator<input_iterator_type> find_iterator_type;
            typedef detail::copy_iterator_rangeF<
                BOOST_STRING_TYPENAME 
                    range_value<SequenceSequenceT>::type,
                input_iterator_type> copy_range_type;
            
            input_iterator_type InputEnd=::boost::end(lit_input);

            typedef transform_iterator<copy_range_type, find_iterator_type>
                transform_iter_type;
    
            transform_iter_type itBegin=
                ::boost::make_transform_iterator( 
                    find_iterator_type( ::boost::begin(lit_input), InputEnd, Finder ),
                    copy_range_type());
            
            transform_iter_type itEnd=
                ::boost::make_transform_iterator( 
                    find_iterator_type(),
                    copy_range_type());

            SequenceSequenceT Tmp(itBegin, itEnd);
                        
            Result.swap(Tmp);
            return Result;
        }

//  iterate split ---------------------------------------------------//

        //! Split find algorithm
        /*!
            This algorithm executes a given finder in iteration on the input,
            until the end of input is reached, or no match is found.
            Iteration is done using built-in find_iterator, so the real 
            searching is performed only when needed.
            Each match is used as a separator of segments. These segments are then
            returned in the result.

            \param Result A 'container container' to contain the result of search.
                Both outer and inner container must have constructor taking a pair
                of iterators as an argument.
                Typical type of the result is 
                    \c std::vector<boost::iterator_range<iterator>>
                (each element of such a vector will container a range delimiting 
                a match).
            \param Input A container which will be searched.
            \param Finder A finder object used for searching
            \return A reference to the result

            \note Prior content of the result will be overwritten.
        */
        template< 
            typename SequenceSequenceT,
            typename RangeT,
            typename FinderT >
        inline SequenceSequenceT&
        iter_split(
            SequenceSequenceT& Result,
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
            RangeT&& Input,
#else
            RangeT& Input,
#endif
            FinderT Finder )
        {
            BOOST_CONCEPT_ASSERT((
                FinderConcept<FinderT,
                BOOST_STRING_TYPENAME range_iterator<RangeT>::type>
                ));

            iterator_range<BOOST_STRING_TYPENAME range_iterator<RangeT>::type> lit_input(::boost::as_literal(Input));

            typedef BOOST_STRING_TYPENAME 
                range_iterator<RangeT>::type input_iterator_type;
            typedef split_iterator<input_iterator_type> find_iterator_type;
            typedef detail::copy_iterator_rangeF<
                BOOST_STRING_TYPENAME 
                    range_value<SequenceSequenceT>::type,
                input_iterator_type> copy_range_type;
            
            input_iterator_type InputEnd=::boost::end(lit_input);

            typedef transform_iterator<copy_range_type, find_iterator_type>
                transform_iter_type;
    
            transform_iter_type itBegin=
                ::boost::make_transform_iterator( 
                    find_iterator_type( ::boost::begin(lit_input), InputEnd, Finder ),
                    copy_range_type() );

            transform_iter_type itEnd=
                ::boost::make_transform_iterator( 
                    find_iterator_type(),
                    copy_range_type() );
            
            SequenceSequenceT Tmp(itBegin, itEnd);

            Result.swap(Tmp);
            return Result;
        }

    } // namespace algorithm

    // pull names to the boost namespace
    using algorithm::iter_find;
    using algorithm::iter_split;

} // namespace boost


#endif  // BOOST_STRING_ITER_FIND_HPP

/* iter_find.hpp
HW7DaiRbPXg1Y06Vd/l8GrM6zlWimNPTKZEFcSLmGA5tF33fGkfdfcbk8zOPD3c6RAwWYL4lcj4miMSM3e/TJTmRhGY1s1OJsEdWNasTuzjvDCizNCElNVPheGGGEw2pL/VD5SmEAdtJvHQY9LFG1PDvx8G/zgArkQ+RBDfRLxt+Mc9GMx+32CDGPzU+KQ8UrkGxPtsvFHbAx6lxCb2t9wFWLGUpscu7teuw9r7HAFtwy/hJxpAIWW7xEJkl4jeHyTEW7oHv97FpUvu947q4225Bi9hqCfhIAcPVKHxMBcYOn6BHHOmTlRku0iF0SB7yLY6BF8AI+NBkrfH8i4XMb6O06AKn9Vt0rpO2bbrPHULMOYyzK0Y4iz0av/fNmgd4Sz9R3yrkyt5R5Yh+UU+ga9+n5HJLEgzJKRPPFa7xke7NrPgeG1csURzenXIbhxrez2B60dXRHo/cqkPu6wfDaWDJfPO/ex6QGSOKg4tFwbxL29tBQGs6R97NZVuBaSNxTqFn7aOn8PQIeIQ/DbtghEelOWSjWy5xNxt6grwrD7Ozor1ffxY6vGd3lEeDe9gVZ3eRVCxb3p7h+xHc3KcSjRDecrSVWB4D/uOFV4Vv/P6FKfmi5Xd2fMVuOpVVmXy5+A5mJ4AoP36Yf6jr8KO8/4X8ASEaw1TkAJzufHA8IF/YoLin33Uxs4OgIv2eatFMy8l3rz3m+91C6KQQ2FSwJ1BMI4fgRd8L3eshakHaBBXQBV2JiwkdR4OW9Zdx150z+B6/QmIjyfV5k/e7BF+GBz9xKmFFUyXFAJH9nPs8NHIsTRsZT4yAB015IzosVlGcil3A3/QhJn//rqHPEFIVmiCozd0On2uL/DKBATFMWGrnapRQj9mNcZPYiye5WyvOGV/qdOZCV/ypyqRhiXjcLCDP8NNHqwNkSINc6t5gIHgPIS3RzfuvtvZsGjTClo4OECv1hj49AqCZAr3RPl4OWM5T+sxBlKVSqdE+0asAi39/t7WNfnSXUWhPuOh+4hEdjR/J/QJA/8RnO+H19q1hVG1b6l37uaS/DwTWK4EmEPJysgHMpwJlDWgTTKF8cRzre+7wGIjw33hvmo9lV+orwAD/vQwAhpINXKTIpbAG4YbTtDGTm36Ht1NNWYiJmGuZMjYat2/yywzReyw2Gud9q6Cm7eBFbOTVkLMcJ4n20HbsAaHOWCP4Ab60WijLdOUSlCbR3ufCff8jHZUZo7HfbpRSlwT+Jv4iKq0dI4uvtqL7GS9lXkSGfdfxUcx4itw5/4WAr/shx0IeLlFtqEFW7lohABw6Iv8DRDK5rCDxE0RP9hUJmOzh59aVltS824FhP483ua1X4YpMw+fQafgpcwSLEHyQaGV2w8eR7w6LxAXo60CoKbcIO6m14MM285h8G/jGr0yhdwY+9oVstuk2Ud1o4wP6NjwdAcvJw/eY5sNl2UwzjyHjViGBb0KIhOhD9FTuZB56YkOFpg08wkckXro3wSrej/NhIYKnYqCFj+vnJxIJ/gJmLYkBq+nl+IwSghyQINCHTFg2Ak4qpb4h+8Wm8lgmH8oLcBp5TIe7Cl7UalYcdHkRp1NKgBDhMPzCOb5F5unDZSphjTRbMwL1nYsSAuPiywyYWuQ+dVrsDgILGop314/WJbGmyU/Mf+D8oVz5dOLCNS887RYvRgJLmt1g/daxFLYcmxI/kPdPnwkawcsTMKr5VUTHlBdMYAtg+6MhPV+UNTnufG/JPz4VA4ZBJslTD1pvXfSE4TfQ5tP9czy1amJCjZncIOFqDIWBTUGye5fVZq05c8qeoGkpS7iIyyGkjQrJsFmKb91zzI0AaUwZ8eTy7CjwdmPiUjcC7gOZLEDIW+MFJQBm5+drkwP72dMm+5IRCg49VY8k7R9Xtmf/rS+u8hlj/PTzEd9IGVybt1DSZeT4DKIDIBO6faGcMVAtJFn3RwpHtL/H503k6no7doXF1NBuzs9+iFSbgvIc9DYasivKQYB09ghvPcoTjEf1cdbPk+IMiUuAGg1mB7jBqNj2VmAGXE4VmYGxjzSi7vWRaX1ZhJ9By0dwAOx53L+M2UY/grf1ZI1MdgJ2P95YYOUIJo0yyKwrCY7t1rcbMCm5I5vNK0NpxjgpZVIinZ1eWV5LZxmN5HnlsSbGwJ7eA5t21s2AEBsCMac6tEsEYYz5grQS9ZxHZlk32g1EaHIY2lSmL1QpUqWZRJ3NhIDRIYV7XN+6MSy6DzTVOxaXJTD+9/ZysEhlNFhvHX6vVDTkgtPcT4EgKiGl53CPIz2CuSIStkJ8HvWAXVCV9MpviGIjRLtt82rDj8wo+SBVKa070p/hA/4CuGZKRwcTbTGGJdZjecIYZyMcctQt4X14JFObQOhL8rK2wrwMKpdORBfjkpGgH76X2DQHQqboejyyh3Ou5Zw6xFX/aAkbS1wOvrcQqJQPxpbz5TPJMnfUzFTz5ZNsCRTtJoLwjMyH4MVj2jlCaFo5efljVjlBZjzBPDmeCh1bOq/frnGjnC0XuqxfrjBhLa9VyTFbkoXBFyW6QQ0qYPITtM1njL3p4+fXykbjm0ZCoyOmb4AXpPxLSzJ8YbFAihM0lvecfjXHEq/KFr4iajLjohnXrtrfL0DVeSKfKN4CLIXWybsFM7Ine4/s0voYj1Rgmx4G6qYKxrNQ2PTiNMT8El/lnxR272yKhDmZc0DWCjGIAvv98Ej7Xg5dRGJ0Tu88G1as8ZynGP/PuWHVuMTLMR/oqjlQEPOKtW+Pk+sSlVcjHjNgvA5HRX3yzWjlXzg3ibYLmvgwPAAW9uUwH9U8gQGYk2Zl3OEE8bMGNOLI4UJ27qKPndi3mfG/VRFv0++teqiW0XqLEJEAH/rRlSlIvX+ZAv/cdOkKgl70J23UidvrPyycWcLJjjE9KZkMW6kHR/JE+NI8xS3Do8bXYYQW9xoZ6BZt06KT2ZKRVjBP8UUXfShmVSZSsdaxRkKR01PZmPvs9gRVSgCkPO/fMVgac5eHlRpxefyXQNuzo+Bhg7/O2nBPwLoDm1VOLT/9z38MEWewLhaxanTDB4ovK7Ic8nYcKBfZH49QpF6la0SSow3uJVyZ0h2fvEHG9CYrxz0J0w36bPHqmTFnc5PT3fijamnKAqXrRh1Iy+qxXRfNsHJWBV/ZId6ZbNbhPllz1SHpuXHiSsrB7DeNbizBxq7fcJYR6KRifM9d9T232SvCFb8P4E3EnTICH54N1rAAgOanc/p9eGLMRjZw6bu6oXqamtv7MZZShuVAIl5WuSsoNBGLaDceFbJpN9WFTdStPZk+U2AS+OSXdw94tUrdT2IOjPZZ84nVLXkwrrJJ5aXwtziPFrrlc4DRdeIV/A7iMa8CsZ7ljgxtgIG/J4xnx+DfJiAS90nVbHTLUgrct4LLpLgCZsH/ww6SI9iRJZ0YWS8vo41EEvEa9MkuDi+jSXVf133jn0EBjrtRQWi3ZVzHfviy/DglRDSGSHHLHhfK+1Rpj3LFTjS7+aD3SULXJ4rwGlAlSMXvFj4MSzYwujm7jscuJtBPbdZU/ZKRWYTBv1NVnj0rf9+UVSRUz1u//uGAlikaHo9y4xJNnFy/asP4r/Z43XslHUVJs4FLPjCehVCaWQWGw0/XkLh4NqhSPtXtZpaVpmlpcNWwYZV4wZDpn3RSWWh3jdQxyyF12RNDrspyePXTmqhz2xESYwvZGfX2ZsChQs07Vq/cBlHwfAeR3kYbb1ajvh7mwjF3qp2vvSqEhIJYOxku6Sg3lVN2WY2ak7raB9u4oc0Ky6jcSmPLwkSSfgSSlZouvh4tzSTywhjVasZNiG+XVr5CYxfw0IjH+la7F2A2ffTHKo5hkhTrJg9mZhl55BtGFQxjhkvU+kNQmgnKJ9u21X/EtC2U2+zRG8Qaq8aBRJQekpl8GgPTdi3OXvJkxnV54SKRTHVkxrhNWUlysQ3GF0mOVxCZNDaS20yv535YgQz2lhjCobqZddaSRZGDffl7c6XsFGU4j9Sd0JyLwOfpbresm9ybLM/WTlgukaGkaozZs8YJ7N4PFjWiYDzGYN2lbe9fkFoXFa+n5zouvzMqrVc9RJfPSKrUWC0H8uud/7Fp5N5DC3nzaMiNJgVXihUXezTogHcoMu5XbTBDLzvS1Rmnq+4KBD5/8xhqTlomD/GOXhot8o7eHlnYOmuz+roFjhb9shOAgEHunuZtgvWmAfcuXiKZn+p/dHumrmYOoA8ah/6GkUeq3ZvRq0vTIfTEGQdfyWhWaxPjc8NZ0POmdvntK/8sPXNePm7fhkS9wcE5Qscbc5vzJyf7H6Z7viO4kNssCW0n50dapOLMrL6TLulVlxEYdDDgE+7+cz78KutgGRoYfCums4f2PeOra9E8X8UH7pZimLvvDXQaqkKSOofI8rJg4xq/pFbwhfoF1LTV7+jFL0PgWMkbM+D7N+YFd350/Wp5fha8369uMWpDXS2bf0zHTxioJHxNHWESBEG7u+ZfxFxVRdRwwB/14H50sx/A/f0hcR0bIlt8GmFRCLSFyD/F5ag75rG3Qq631eRrwIGmmzoovnbEp1/vdRUcNIXgO4Ks53WD+vQ6mdwQOxfcvkbK4TtrNDhcpL/rUuv9Gvz9+/sLBA4AAPwH5A/oH7A/4H8g/kD+gfoD/QfmD+wfuD/wfxD+IP5B+oP8B+UP6h+0P+h/MP5g/sH6g/0H5w/uH7w/+H8I/hD+IfpD/IfkD+kfsj/kfyj+UP6h+kP9h+YP7R+6P/R/GP4w/mH6w/yH5Q/rH7Y/7H84/nD+4frD/YfnD+8fvj/8fwT+CP4R+iP8R+SP6B+xP+J/JP5I/pH6I/1H5o/sH7k/8n/++6PwR/GP0h/lPyp/VP+o/VH/o/Hn3x/NP1p/tP/o/NH9o/dH/4/BH8M/Rn+M/5j8Mf1j9sf8j8Ufyz9Wf6z/2Pyx/WP3x/6Pwx/HP05/nP+4/HH94/bH/Y/HH88/Xn+8//j88fvzv9lz7jktViX3tzyWsaDsfs4r+dRwfc3V89vyszpPMKXSP940L3bqZ+byBfsPerTWfCYyQTBmeNmh/gf8ODL9zAMM95qQJ2aW4LUjNPDvkwGoUsYUdIbCkyYNh8sCqpRcV2sV5L/hez+Fkq2k+hnexRQcMEezGUgwMr92f9/3pA9jsG8xHB5EoRYXnXu8d43KJRI5erIxk6RkWhFWAyeUhlXC8cNRkDayAdptLUi/HGks7bfw7UE+IWWHYDyHDiYfzp2QO9wOFQDwMrh0WPuse2Jse4/coggo4phsXK6UMnCTfsyuTf9DWFTVCnOWk1idejtV/jcUkh5IDtC0Nr0MdwEQ9QeeEYitRAaEblRKVuR9UmNckBMOgoTU66/T6bnCjGI7rI7sGgUQD+BEBOLUUmJR5UnMsPZD12c2ra7gRuBhnmvT+7jkzw7FLWJFPNEFyBFpAGYDJmgOGD0lddMfxxdQR4gFFEtwqCscqzIbd5G1CJbYuhGTu7tTrrTU4TZUUfpEJjTVZawoxx7zvQgj50EedUCbchyfKt78aWJgyqFAr4YR29sh/Gwxo0Ifklpq2mBG7P70PXkzQvnFXBZEre+XWJG6Bb5eHmECqZM7u869V7DXDQ6zSfZNpI+E3RyPKxbrQ2Ltbi8oggx9DPBCvl5wz1fLHI5XakkBpFnuxv9YbMXDtvGAX+1W8zlaObinKkvoYc37r4HzlLiIY9scMAZOwGx/DI6fPkBf4nAPmsHYgELAX0D2A99we9CJ9mCjQKpwFwAHSqvzyFKL13M+IbuyJfBhpN1w2aVrKnc7RASGj/q6HL4I/E00wbIR6k46Wtjbiow5d24a3HP/3UrhBb9W9Do+fdjddo9020ad84bO8ujhDwHRLjG1BtzyGd5Ma0LW7wDZH2dwW9XPWC8OIBivtiz4MDyYny3exFq9Sr7mz4Y8JLyRy1eqpo/3I4baX7YrmQts/KPKRBxmGir+SOKo5iRZoLxdszEA2ouxraE96hj7T/Ra2Y6d7qgedhIVm/v4I17+IqdjShjAVhon5j/G4KcOsmBUuA0bNj1OOzJjv9sp0iNY04vFxHNJl6Tt5ZXGwelOIQH0aVC3kFIghNIYuutT4U0wvgkMH66FmKjxMEDF69SthGaIb6CPLZilpVyTAZ+94nE7xR+pBG9ub4jxDUANQme9vCB/faW3nDkZMG5M/v4kDmZNHDpQasJzlYt/lTthdOnlJ7vLIGpDjG9uwzPm1+HCqj2JwNOJSBqGe03fsZf7aurecHq8/m8KehotZIsQ0z024AzNjXqhoq1WeUkROCFtznaBa8Xn9F4e9e6cJ8MfJyNoL3uz62+kzPPsj6lwl0iXwpVXjtMz0xqKlIvA66FYz7Ltg9NuPgoN3zGZdWJZ0asUbbMhhO68jA5HnwUC7vLIBN9olaYRtG/Uvn5HaFfFtjzy4V0oPwBlCgOROjb4wUH0ZDgy1E8/Ud5ul6JNG8d6Lso/6aggN0+WoCeo8d4jF0jY7GH/9T8ADkR4HQVvhpcpAZViu4aBAFBuGrR4QosqO9+8c2ODFomZ7cvu4mVwriMtGVL4CVOkQjKZHAnpekbK+9nTxXKdOhdZI28i5Td/tDSIESa3lNvfdjvovFbpiuYbw+pGNuBZzMUwr0iMZZc1sidgd9p7oXx5gN13KyN4T7Hx61F9oDdm0oPPslh4MRpPcdWgnTohBN6b0+J6lUd0zyHMbgL0KAlVmDkxJEoLex+NoHsE4MfEYEDH8HThFL7cdU1Km7OyDg324jf3Z1bnqdq5xu5gA375SGQvKoZM7sVO1Td6BctmzE11cGfvdCxUUn++xvpaFbE4kQCgdodd2gJblIhCI4YT3xEb1N+MJSNfx23eBaW2pfESiLWexwmfYnom4er69H2wGDTSr3SIXNsFNRh9nHHUCACUal9TX8w4wXOOTuMrlRGLr9Nx9Ll+GMbLAD2S/XYkiSdnC4GGq4pRrHBjdjMBjY5/qwBQy8Mthcnd2gopVp53YUhGunFQn3SoBhB6JnFC0iflJ+L4rapeiFTxvTfIjEjUZbY0u3U2ntAwWIibwion/nc6cgvL34pjyUp+tg+ugmaLV7kdfeYQnkp/mKX5GDoZfy4xMXAYXYByGJrrdP9MYfiIcrTIkjcZTW3kBvHfKB0lkajdWPCQOTk5UU79x3rhwazMeJQPmK/xapSH9Aojt0/ObdLrhnZuI/ZKPfqjmgCxUQ0MDuANA+89sHoxomAXoy+HdTw3pngcHRTaoZAY05YCZpotIkhcPbvsHeDHsRK9EeZlIW8Spbxt5kGgFMDoBCVIDBnTFdXJKEIetDvpd1K0/iQ94wuCWXrDfuE7SZIFsMsQA9e4TQbMICqSHsG47E4LFC/zW6j3ENGL3pQb3SLvGemHlJpWJ+PZR8qdmxDU254t7y7we5odpmnCqx/7L9ROxy38yGCngX5COPODztmnHODLBey2J+71orBg6RRtBO9lTh9wyX9emLaVsUPfmFdp/Ct8nOsFvKF3uDFCeXva/xEn3ZgcGA8Md53Kkm7HxBUzu0AqBvrlEI2xof0bYtYruD/HTjGfg74JeR0uXr5P8vVTIRSdTeKdiNeXlh/nU9IHEyKVNlRavkyVoGOIUbtJntXDTWbnO1MfEfSycQnhENOe49aECTK6wgO4+viux0qXDQYPdgE+MU1jhZXibvBhcKXQotC5q6Re+TxbhhyNakoyYYK8ACFz2ev8t8IN7makCtXGlza62ZntYyDAGkR5BCFPj7SCzg/wmSzEEg4agZx2fZaJn+YJoPNxKt4Tn7dsKlwEsLEF00+7rRNj+5yK1c4W9MNld9+wgiTdDlY5J/DFB90sBb6PHEc/yL7HBIyhqP/iAt1B+BsFIFIr/0oqWQvkxv6Uxn/khHZ0eD9ATQKtj34Cl3h0DI/eoLOkBVYGG3YLB3ii5+ArYHFFbUu8Ke1+WxpLXMp4Wya4OMVhaU42mK3HeW7di2eIswm6009bsX6is4uq+p+6mEd5m8dirEJNTj23tcOXZkiRTExJ4JPh+HgcEErVyhfW7OjqDtYLSNh2Ck4B5J63XnVDaAa9da7lDxoQzlZU/mdViWR3Ix32PjyixVWEhwF6v2r/TC8TCMPn6masqmz3ICTWQ3MBvb2fbHcrZDTAf5KwQhtUaWRazh70O3t46yTb/TpWXUfGK6keqmpfSqe7/052Z+0Ff6JIN3I10lxhXqTDgDDJfWSbeF9APktdu0ZxgL7TSbrgY3er295LpIPsRMztkT4BTjimah15Ce5e19ih/EPxOCPJu1zVbnzAypFS+OHgaWpgThejjVw8iNNubp2o2e5Ge0U7vjcRF15U73AU8+sTePpmQbaZRXH6uvt3vy4JgXU8xZwQeaWpcgYjWkjMSEH5ArdxvnpApDW8ATbRjMt2NfGDo45DczWzG+N1iz+sXnQ4sk+MH70wrn/T19+tSseuNaQIAHBk4Lwgs1Rf8ssvV0tpgUaUVx1XLVS5/hMlxtLnn4oMqsn7KlUtaqcokJXRFD9lW0t21C9F6sJIkxor3t1m5CnzZHqrh7Ix1N2KHtWWpVQTWFLFdJtd+CoFbg27F94fNQVNh5hJedh6YBg9s2lJWK1cvQd4GDsfF/kVmKWeViZhu4Wuuwmi6eEpc+vaX2XYVgiyHUyTY6drqpyHqmSXxMZYd/ZM08zqSwAE44Qa9duthrIqnOdVW9TQPv+0wdZgPGL03VkK7EikTn2CpEZLP0Qt7d01LdM9jKoa6QDnZGyG1L7KXR6TklfbMvX40hrvx27lxTXonjG4D6a4z8ZPPurf3Zy9S0y9XPaWEoCMxzPy+N1+CJyMlflvsiMUowmvNZW1ot+pP9jpjcMtPj1QJYGY34nXtikdibcD9KfsFOUsAJ5tZF3AtFg+DeidL4TwW4ZOwo7rruhr6vSlmGc6wO9nFmKspOh0tYLevXsfPebEFHDuNNKchRKKUP6eVdLW7rhj/1s19DjfLL9Z59lnqqKPC8JGqpvf1LchoG8KaYuzdDnilhywTk/Q3WMGcHFjJzUJwg82fg193UnB+Sbbf/gtZSNQAbLu+F+0TE9+vmoU6v1LrXzOMAXlQ2rd9Pg1T0wpumOBnvgPoGg9umk2zwjSRb9aB1nGZGVqyiC4/Nbt3rghQ0h82eGSBCR/Mj8=
*/