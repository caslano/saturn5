//  Boost string_algo library find_format.hpp header file  ---------------------------//

//  Copyright Pavol Droba 2002-2003.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/ for updates, documentation, and revision history.

#ifndef BOOST_STRING_FIND_FORMAT_HPP
#define BOOST_STRING_FIND_FORMAT_HPP

#include <deque>
#include <boost/range/iterator_range_core.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/const_iterator.hpp>
#include <boost/range/as_literal.hpp>

#include <boost/algorithm/string/concept.hpp>
#include <boost/algorithm/string/detail/find_format.hpp>
#include <boost/algorithm/string/detail/find_format_all.hpp>

/*! \file
    Defines generic replace algorithms. Each algorithm replaces
    part(s) of the input. The part to be replaced is looked up using a Finder object.
    Result of finding is then used by a Formatter object to generate the replacement.
*/

namespace boost {
    namespace algorithm {

// generic replace  -----------------------------------------------------------------//

        //! Generic replace algorithm
        /*!
            Use the Finder to search for a substring. Use the Formatter to format
            this substring and replace it in the input.
            The result is a modified copy of the input. It is returned as a sequence 
            or copied to the output iterator.

            \param Output An output iterator to which the result will be copied
            \param Input An input sequence
            \param Finder A Finder object used to search for a match to be replaced
            \param Formatter A Formatter object used to format a match
            \return An output iterator pointing just after the last inserted character or
                a modified copy of the input

            \note The second variant of this function provides the strong exception-safety guarantee
        */
        template< 
            typename OutputIteratorT,
            typename RangeT,
            typename FinderT,
            typename FormatterT>
        inline OutputIteratorT find_format_copy(
            OutputIteratorT Output,
            const RangeT& Input,
            FinderT Finder,
            FormatterT Formatter )
        {
            // Concept check
            BOOST_CONCEPT_ASSERT((
                FinderConcept<
                    FinderT,
                    BOOST_STRING_TYPENAME range_const_iterator<RangeT>::type>
                ));
            BOOST_CONCEPT_ASSERT((
                FormatterConcept<
                    FormatterT,
                    FinderT,BOOST_STRING_TYPENAME range_const_iterator<RangeT>::type>
                ));

            iterator_range<BOOST_STRING_TYPENAME range_const_iterator<RangeT>::type> lit_input(::boost::as_literal(Input));

            return detail::find_format_copy_impl(
                Output,
                lit_input,
                Formatter,
                Finder( ::boost::begin(lit_input), ::boost::end(lit_input) ) );
        }

        //! Generic replace algorithm
        /*!
            \overload
        */
        template< 
            typename SequenceT, 
            typename FinderT,
            typename FormatterT>
        inline SequenceT find_format_copy(
            const SequenceT& Input,
            FinderT Finder,
            FormatterT Formatter )
        {
            // Concept check
            BOOST_CONCEPT_ASSERT((
                FinderConcept<
                    FinderT,
                    BOOST_STRING_TYPENAME range_const_iterator<SequenceT>::type>
                ));
            BOOST_CONCEPT_ASSERT((
                FormatterConcept<
                    FormatterT,
                    FinderT,BOOST_STRING_TYPENAME range_const_iterator<SequenceT>::type>
                ));

            return detail::find_format_copy_impl(
                Input,
                Formatter,
                Finder(::boost::begin(Input), ::boost::end(Input)));
        }

        //! Generic replace algorithm
        /*!
            Use the Finder to search for a substring. Use the Formatter to format
            this substring and replace it in the input. The input is modified in-place.

            \param Input An input sequence
            \param Finder A Finder object used to search for a match to be replaced
            \param Formatter A Formatter object used to format a match
        */
        template<
            typename SequenceT,
            typename FinderT,
            typename FormatterT>
        inline void find_format( 
            SequenceT& Input,
            FinderT Finder,
            FormatterT Formatter)
        {
            // Concept check
            BOOST_CONCEPT_ASSERT((
                FinderConcept<
                    FinderT,
                    BOOST_STRING_TYPENAME range_const_iterator<SequenceT>::type>
                ));
            BOOST_CONCEPT_ASSERT(( 
                FormatterConcept<
                    FormatterT,
                    FinderT,BOOST_STRING_TYPENAME range_const_iterator<SequenceT>::type>
                ));

            detail::find_format_impl(
                Input,
                Formatter,
                Finder(::boost::begin(Input), ::boost::end(Input)));
        }


//  find_format_all generic ----------------------------------------------------------------//

        //! Generic replace all algorithm
        /*!
            Use the Finder to search for a substring. Use the Formatter to format
            this substring and replace it in the input. Repeat this for all matching
            substrings.
            The result is a modified copy of the input. It is returned as a sequence 
            or copied to the output iterator.

            \param Output An output iterator to which the result will be copied
            \param Input An input sequence
            \param Finder A Finder object used to search for a match to be replaced
            \param Formatter A Formatter object used to format a match
            \return An output iterator pointing just after the last inserted character or
                a modified copy of the input

             \note The second variant of this function provides the strong exception-safety guarantee
        */
        template< 
            typename OutputIteratorT,
            typename RangeT,
            typename FinderT,
            typename FormatterT>
        inline OutputIteratorT find_format_all_copy(
            OutputIteratorT Output,
            const RangeT& Input,
            FinderT Finder,
            FormatterT Formatter)
        {
            // Concept check
            BOOST_CONCEPT_ASSERT(( 
                FinderConcept<
                    FinderT,
                    BOOST_STRING_TYPENAME range_const_iterator<RangeT>::type>
                ));
            BOOST_CONCEPT_ASSERT(( 
                FormatterConcept<
                    FormatterT,
                    FinderT,BOOST_STRING_TYPENAME range_const_iterator<RangeT>::type>
                ));

            iterator_range<BOOST_STRING_TYPENAME range_const_iterator<RangeT>::type> lit_input(::boost::as_literal(Input));

            return detail::find_format_all_copy_impl(
                Output,
                lit_input,
                Finder,
                Formatter,
                Finder(::boost::begin(lit_input), ::boost::end(lit_input)));
        }

        //! Generic replace all algorithm
        /*!
            \overload
        */
        template< 
            typename SequenceT, 
            typename FinderT,
            typename FormatterT >
        inline SequenceT find_format_all_copy(
            const SequenceT& Input,
            FinderT Finder,
            FormatterT Formatter )
        {
            // Concept check
            BOOST_CONCEPT_ASSERT((
                FinderConcept<
                    FinderT,
                    BOOST_STRING_TYPENAME range_const_iterator<SequenceT>::type>
                ));
            BOOST_CONCEPT_ASSERT((
                FormatterConcept<
                    FormatterT,
                    FinderT,BOOST_STRING_TYPENAME range_const_iterator<SequenceT>::type>
                ));

            return detail::find_format_all_copy_impl(
                Input,
                Finder,
                Formatter,
                Finder( ::boost::begin(Input), ::boost::end(Input) ) );
        }

        //! Generic replace all algorithm
        /*!
            Use the Finder to search for a substring. Use the Formatter to format
            this substring and replace it in the input. Repeat this for all matching
            substrings.The input is modified in-place.

            \param Input An input sequence
            \param Finder A Finder object used to search for a match to be replaced
            \param Formatter A Formatter object used to format a match
        */
        template<
            typename SequenceT,
            typename FinderT,
            typename FormatterT >
        inline void find_format_all( 
            SequenceT& Input,
            FinderT Finder,
            FormatterT Formatter )
        {
            // Concept check
            BOOST_CONCEPT_ASSERT((
                FinderConcept<
                    FinderT,
                    BOOST_STRING_TYPENAME range_const_iterator<SequenceT>::type>
                ));
            BOOST_CONCEPT_ASSERT((
                FormatterConcept<
                    FormatterT,
                    FinderT,BOOST_STRING_TYPENAME range_const_iterator<SequenceT>::type>
                ));

            detail::find_format_all_impl(
                Input,
                Finder,
                Formatter,
                Finder(::boost::begin(Input), ::boost::end(Input)));

        }

    } // namespace algorithm

    // pull the names to the boost namespace
    using algorithm::find_format_copy;
    using algorithm::find_format;
    using algorithm::find_format_all_copy;
    using algorithm::find_format_all;

} // namespace boost


#endif  // BOOST_STRING_FIND_FORMAT_HPP

/* find_format.hpp
v/whe585Mx3PkM1aRsFlykZpaWlAkNR1/f2rB1L2tfWv7OfZx8Hhn47HBY/zTmA7CTVvPeHu+X5pUDBOGiUfLBjvcBzqlGZxbBsuCPNum720R99mZ5png2VX8ErAM2afSm0u5BmEq8beG9FUxDV8ofrqwqiMLCgoICCH0NJ2/pKDoRo+v2X/+q9aTUiWOs62Psnrhh+sxSuEtlDjWViHmYyVkX4bEBMe2xiwcy75ZHmHsedSgCMcTTm2VQfUdGBWsJft/lqiTjhpEfy4ojSv8LxM7Dzz148G/t8JTtCx/kPAif8fc5nNFP1VAIBDS+29BVBdybqwvYEgQYO7u8PGPbi7e3CH4A7BgzvB3d1dghPcXQLBgztB8ofIOTNz55xz/6++ujNf1d3Wb3fvvVhAra7Va79PP/8/tBkMT8kt4E+rMP/uEiQSIb88MgrjsydtBjGzgJ1P1rqCYvQf840vxJ7u5iBz5Kb/fKHjlOO3nfSFiYh7oeWY5fupDBYd1/RV554fBIIUBoPbq66urr4w6M9YDNSlpu/Lq8jtMIjkmtb4W8WXA6Hi6JzHbZCcCX1JYdIusLtOyVQWaec0taby9Fxiqa3QPpeVm01WtorH14c6zs4x76mZy6zqnugVcbl6dwbmHm59BUAwJpvDhPsrgUkcY4ywgPd1UYHkOYcZJ/t+0kMFTLb0RogmhuJEMqJx4OmTc0gOGunk/75AU4e+eu2rhOxLaBRVYQJFys9O9I8mYlDq1vGuto9eXQxELSOw1KuQB/9sQjPM7aIgTNGMgMj/8xAHZnV5gf7I+8VHnavtD972N0Gg1w2skncZPSrUqP4Jc1osioLPacsbzfMDkTS1X89Iw+pd+99q3ofxnmRQe0cHrSJv2Zw99yJZS/QW+H2BwgK7UJD5/gI/UW6ayTjdD2zcS09QbiTZDRaB/zYorn5Qzm2yYBZPYYmS/7NEhpqrpGUeZBmV56vE2YokAigylpJtMdDn4ea3MYBgaWud16kerEcdCX2kLE2uXbYnS82Pmhhxs1s7z/u7rT/fWupHhA2Xh4EAwkJmq0RFjFVFAG9EhC3UcnKYqHMAL4mJ6kota6nUakDV5kCjq8eL9IefG2hBiwwJ5IUykIa/pnze6Q5tC57fAW9/6f+xLYDdd0o3iONL12udrlR+s4ru1Af9CdNae2J73OzTdcmujOmlB+Ik7MRD9EhoHZTH/LU9nIHlftNWF4WTgkvWrwCxJyMGKmQh4/hLAl8qBDmDJzOGEl5mPxu0s/EJT27FkoFAeyBHo2ILm88hqdcSFuoF40hX2kIrghn11fx4RZZfelxjcg1pWhIszkVez0wSzcHAq508OrLSDybGgpB8JBtqSQwHha92NlMlkclw42Fx7mOD9Q27q7Pe5D5OBef4UStBtq4WiEHLHrInswPrXrqP7Dv8vmtPGSpLCZADgPqvwV/KQjAw/K2+IgEDgP1BLg4Agfh51gAKAvrsKRXvt0qMZ0iEjODIKPxAAXk9W6Z1Yp8nGOL0jzRE/DEH9aqdwnL8hPAI7QdtFK3J76FMl9M54qliZVprj4fSAbkNIz5qSE1FYkZyr/rcsOyIfunnbfLtdP80TEuzXfGJhL4fYRPltzvFwrS16c+nGVD/BbAfT2HH/QovP5aMEIzGdovOuUNv/3cd76ZTNmtdz7fa6xcv2nPXSHPGMmgv6+fyLsluafE8bm3K6tuYmNMrHwOTkmXVvAWlRshL+bKyXNMZk5qEtEDBj4vqYIZPw0YGiT6+oPeULtQxCTO2lkcH+LjvWylRZ41jZWnDv5mB3nWAaDoiDycT11csrKz7nL7hMmmYQMoZCqPzm+Z9tZso0Q9DiMvIWVjTVacEkbEJxI3kAixFBhv8+OQ0oq9l/C3UGEuIBzGWTSC99f485CejZBYiYXIedsAdvUDSjxUSEGTz6OdfPv5dhwF+Wtc2d+Nh0/JDYR8fV8Cwq+2SfdOdfJiXM0zi2af6HfurEoZWgZvEOdbtGWP0t7rIWNvLi6VdpzAbBlpLKUqpklAP9pULpeYypP5eTfOWsyzkSF18WgesFlg+lZHTZI9oj8UQXXxyKTeaXwqxoR4EbNZt9qu5qc9J13r4fNTxUG9jjjfw35dGQt9/cD5F+CgXxgRGU2DUiA92LMAwDFudlvDRA6ENqpsBOOik6XPCe2H7Kk1fzrlubARHjVwtDvfQ/lwU7fksKaS71v2MCyx2qqVoJRuLDhjEDjbiAdyI6pvOpr4edzB7bZobwzhQkexm9ZMnyEHYoWY9Ru45VkiIFHRNSU5xFNS0rvdZdixo6f7ufi4oC/rafWHu+xLOZs4iQLjw9VcAte3HaBi0V8N9210rJf8iLjIJ8sIWHdEKfJR2vN/715UHGp3pxwR6c29J9Dp5CFTiFpCiYoKuXOdXLCxCGEoRBxD5oYmmTYGhiWbIIrpKlmV3WEIT72awqb36opmNLkUG16oKM0oFL4bci/5YlpGr7ezFX5PVphlk5KsuJ09+11/Ymc8bUJaGJ7VBzFgyxs2KDK/6mddjDFoQG9vw18kPs4gyzPzV+gvWv1mmxL/kGrhffBsDwaCgnoGDPP/nOPcjxxhdOW4S7dskSck2dgKZTb6GVUDPrrqKiBjIpP9t2PvDKdn9dKw4U1OvGIKoRd1RPhIr2Vi3sRRmcal67ti3h1niftQevCMH+dSH5SO3lOfEyCbrNSfqxYjGsTzfHvkGu0yBr9sMZRek0mWpmIH8+cXmJOso0ceEcfXPb72pYYcohjV6rjtQg4ziVMwMjiN4k93BK2WHbtWM1QVmydtuSrlosvIi29m/mB2gdfLRb+klGcGopV9vVB5UBybw3nzaK6jUfHbfER9oFEer774W0l09iKV29ykyP73TEvnsUQUzQa4u+NiLGn6I4tfmGVwLv9wluYtBq52znI68q32TloEsyVFwShiEUcPTWytPaSwiLgUn+rnRX4jIIAPRtuTZbBlC/kDwLNajX8XqV4DoDSNIadszSmkkec58edpoJBI3uF6G2/y77aHFlwsKo81SHudGhwSaY6AsMhxmaFNFN1Hd6IRhtJX+4ETwxcU3hm/jHDFsGPyl3sdIKArIi16FXoBACFfa1ZtNx0XPqtykZ1+CcMnuCmZTDZacET8kRhOPW1P6jYjOLT9tf7I/qSLCsi0XpmjhlLkm2RsJw/MT+vmLbL4d8kO+G2JXHysG0dPabd1Mt0S3RF8eKyy8Q+EHfx9LXCZpFUPRBm8GJE7skFfn8pfXwKsoVoeqbYtPKfRmoPtOHtI02xk9gTj6w3UhpCQjQrmFbwdJS7MBQqTPmZPDRslMcIVBXkDhECL2BzYHhmwpfTr7/O03fwO4wyWZqD3ymgSb2Dx0oGwNr6o5WUR2MiuDMCOeNideFOGtE3Nw5cyw39s8deYMb41+6ncZnsJgEsfLkcebZCxLZXL9TOs1aITkSlkWM8KirE2KQRLqGpYXOTYUoJagHqj/Yaetr1SQpqtGaM3j+SXyMo2XlxZVT/UwmizPEYs+pjEcsucJ+bTs66rb29clSEMM6tzXjTNvjRKZpa/fZ8jzdPXvbHWVStJ0Gp6vflIhTHg1wbYG6il0DYOf8Q66iqYGPHbMPVwtUN3v5+b/WusF098KnPo3EAPv9wRXcHAwSGjIf55H/YQYkJ8oBqJvMz3luKqazu8kg4C+nX9MLJrCtxEmZ/0PHEOwyzv3TXY/lgRJcmj9vk4b43m9OqMSM3KFGOdYxA1WYp0PuA9JQ0Y1+r3RMasjbaHmQyqTMnkkx2Rw9MK7qUPHuOVDRvUJC5YFVE5mzMX8G1wf1THavJc5ZeNlvMkssiEWejW/nB6MocoYj85JmSwcK2/XllTZMGNPawjzyLP3ptz2ndA8qqe/bUyVan/vVPCZvPnb+0yz3bnBGpjVeUYI3LNw1Ds86EH7t5J2/Uul2nucTD5Dtn97D+mYib8TWShkWy6+g0CrdsfhcQZV6qPUnJCiOyr9Z/I6bnmc3rTyxLHa1ZQRY54SV8qPmZOU+28fXSqOM2Z2hy96dLne7YwVXzg163eclq2fBz/kehC36op4qKeRH7McRCPp1wgvK6cSeDMpP+QKNVT5mbbX9/UjhaQfBPsQgL6UeOVJCZdLCBAQk6SUlAbR0QpiQlBEUGyRmI26E56jRU5h1TmcCahw4LNo5jzrsL/DMIIOeQEVocJEEgDgX8PhRNEkfB9AMo5YqmiLzRLd7W/EO9s7mY5DDD1nwmohEN3twjPuGUrUWMbDc3BHwn9Elt+Yw8NtPv4VoECQf9KQfjUCtbb5/oHyzXp7nI9PVr6GsBJO8YcaqMLyQLz4UnZpiWL27mfgZe+zdMYvofQT9SMA5nqpZpyEBNuqWGmQ7Dq7SkUFIPAQjkZzRHwf3tIK7icWMMq8VcWdyGAXy5H8VOgXpsYnydRzTutOwp9PWrKn4hRhVGH4djm9FOYzo+VDadzDcx+hBgUCR9qrfp+3QFcHL+SjYKTZArF4WvMy9n6rhi3ce8FpQrSGRKt3s8psgkb5M1ONptyQDxEwSoid5sEvomZF3nPtKX5CsXKjIE+oegdUtaLYKgpzHexzWsIBl8LaOKXsdZ0MPMlviyFoQI2TD7EPKHBR1PmAmOMel38cXmXGTJAZOZ6IV4PSHqXwUm6VmG6gdlEBxRc08CIxfXDfKlhiSU5ikkJBWH8fI3T3VUhsEaNrPrQ96guJcAcU/xKOLNSpLkwVg7iQEBch48HWAMw+Rd2a8o5ZqkUJTGnljjchCb3ZwwsKEa2Q7IHz504qgwmOH9PJGHFJLai4huG5sz+HaDQkotfSynIWoLYmXkmJdVss8fRg5o5qUtDPr9EeLC/Vp05bEewqwZ8YzDEiwB8rHT1KbQP35L0GTm2MtxdqZ8NzcaF9VmExVzVr2BpWqbWLRwzogNWpxaPRGiTw5M0QS12SV4u+scRy3L155YX4FtDHLRLQUklmxG9rWWZQsJrtr+JQUpBisno4M8J0beAqzsBRiUY+mVoUMyc3qp5WCYuD3ut+qyzG6zBDU3Whb9Te6y13W9xXCQ1U32hg7Qc5rev2hpCJIX+805Y7GjzG6kXWk+BGywiTc35OvxRCpRRtzj3y7QePuMPQdxdTKSV9q2aVFw677cuuyiscmCs0vVM8fYvqd31wFFUyqbEfst+leeQsNrMH5yjsqLVwuvKKrzEyzPuvRBYY2f9essg/jOjfRu0n4cUTsiDwy3fxHPJ3xrQnZIFR3hYSFY1fWc8u9tu8eGISGZ2ImIRMySdGQD+6uqZrHcisoGjwJ8YLie/gQmKiiqlwIuZmopkKc2quKgfVlHuFw5WmG229JG5jlw9sDQx3ChzVuIwCc3zJiHH9Z+5RZgr5k24rCga/VvZ471Hhw3X7YcGTQu1VHWtk7ilu6kgbMl0kr8Br4l9dOc7vUvzHmMegWc+MTsl3bey4N3VW0bl7+KCfvBZS51InOf/xI+NOdK1ToZ1Yxgt5lYvP0LoZ9vsa4GxVGbBAmw9c+ZJlNoaf9U0bvJUOVN9lqS2n2gZ7qQh84hZ2NybQ8V4sGoImXdB8BRj6HN9PafFNmefrVh3ndmvyEStJ7dWl9N86giuRTIOkqaSlstTS8UAzbgZBAAN2ZE7EVY0/aEywlpdRUGs4kOkHazFb06hZJCQVJ0TeFc3re04fIHbs3KAEvRg0jfpkWtQtFHFWipH2JsQnplmlorLhGjldCq+hjFjfR+xcR4p+ufTdK/mrNOlDZe0YTc1bZjCpb7tSoduHrnP7FvODyab5Rno3faIGmH2yI7iyaVb+C1Tb7IhuPzi7TfnxpYAb7igjfg6ol6akM1PzPrAcY89srgj4LdZQ2JX0ITNJ7CH0Uk9zHcg2TSEKIoGWklxAxswgLq8CgjXK19NTrm2kFMbkigcNuQVQLmtBdFCe5Dca5d1gi+TciTw2Gry9+tH5qYm6TWrlH3MOsVIWi++IIr2N3dYfU5TgrlHb0R4s78O1plRmjbC3plGVItVYULVoL8um3VHsUw5pNluq4PBi664Iyy7WKqpeLH02sAuSE3+UmYgmwJ99wIT8QIDCaIAzUogVdJY6O5HFEZYDWFuTDUB4RuaXHs85m1c5cBXcT4agORtQ9TrXrIAM/0jRDkRUdHp1ptvzKO6LkQftVQtONbMFt8AwIpamoAgzzo6YVkP54ehPrQVRr+/ZMr0ZCrMploLmgcrb+vlIQ3KO/DiiZFSXZepJMSJpHMXwtn3EOc6Td6Ck0T6YwPVjLdn4Ja2rpqi3BIhxYBnbgd/eRyWVzEEe3rZrNdoKVwQc6InVOjwW4tCuCugdD6ZjYQY45R9BXIyHF0QK9q0hWX+ygUdaKQsV/HAstRjqBIYA8t7iym7rtuAI6eI1bc6+jdvFsv9XgO8nL9pjnTtti68AwWY0vyoPXwuScCYmahRJhpB5vcSBi6KQpkgMVS4f8kSJ7Ccq4QaUwBhWyCifapvbXETRONzEQZcatj5ToYMlh7o57h/ri8P8pUwC099q0X6QpwuKvx02vw2aoGBPE22Wb6MmGBgoCBQUJMhvkARwRAgkfmQUVHRCIuUJSEYlg5jYuEl5RT1be5+qPxBeayP3a/8GSIBF19QpMbtMG6UoR2VkickmxmaKRm5ORZSyUVkx/zijfNqrLY+tToZYFj8QvCKDSd2A9a6+bffDcq/5J9ziVD6F582+bUwpefrFd9e3UYdtKvnOWubxyt4cqyZCjhHWWx5HdsU7VcqI8Dx8tn2cKjX4o/dfAQV4SeWLZXtUqfRtTt5TFalDVeqjaXX2S0sZd7EmF0aqtNbR4vnJ4mmjJNKTPFqt7EUlptBJVBeDkiQV8cstU/bL5To4SpUaW1um19bKx1RGSk1ofosABiuLTEejKfUV6kKriIQEM/mJjoRwNrJpWYUWblgbFdMRcdsZVaxmLvfcggQhB5sttSTpwvQ8rXiutOJPPIOuej7a2GkJ5Zv3fHZgJbg2H4++vG3fwC550Fy3vp146I/Nsl4d7cD26FfhXOtcuUT07P7V1f2zZyRlIjxhS2/yubBjgRqVa0/kfIVFS0kYnbwynOLEQ3H7SD5SzBZot/xQ25LywFFvH5e8UvX8XkFeg50j7BLZpZYRes0XOuHcGL6/1GbB+ve2WYA+zRB/rZMI9v1aO+TvWAQkQnlbZMasKhRUIgU7n/V/iyN8GK76TDnxdmUhNslgVjEHsaWGHNhfWiBC7GwsurUcOj9vZ+ilPdAWHkT2syr6yerG867ezSX6ZskL3+swPZ3Ei3UtaK3FpOBtRpL6XcYe8jk1n/0DkZeRyZF3btzO4gEKk9+DuIxneacgO9/0rwaZnzqLDKaCPmM3MMapneG90+9Awu051bav284YbEny888Z3MByU/Jyj5NRzSmTkcc7DhvpDLa7g602Vo+14+r9fTgxFSzSmWmsqFJmyZJCFkI106hlt2hxysvfF8HSPKlVeJCrpMxXdj0u+C5xUwtDiB89d3TDgG94fvu6aQcRHz2ApSJKYKaePD2TVCb9VMRqePmQ1T6ASpt9eSapKuMmVOewk/sUiEo0ZyJOlhc+cygpBmGZBGaSNYsoPZsTG3wTEKLJINBLm0io
*/