//  Boost string_algo library split.hpp header file  ---------------------------//

//  Copyright Pavol Droba 2002-2006.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/ for updates, documentation, and revision history.

#ifndef BOOST_STRING_SPLIT_HPP
#define BOOST_STRING_SPLIT_HPP

#include <boost/algorithm/string/config.hpp>

#include <boost/algorithm/string/iter_find.hpp>
#include <boost/algorithm/string/finder.hpp>
#include <boost/algorithm/string/compare.hpp>

/*! \file
    Defines basic split algorithms. 
    Split algorithms can be used to divide a string
    into several parts according to given criteria.
    
    Each part is copied and added as a new element to the
    output container.
    Thus the result container must be able to hold copies
    of the matches (in a compatible structure like std::string) or
    a reference to it (e.g. using the iterator range class).
    Examples of such a container are \c std::vector<std::string>
    or \c std::list<boost::iterator_range<std::string::iterator>>
*/

namespace boost {
    namespace algorithm {

//  find_all  ------------------------------------------------------------//

        //! Find all algorithm
        /*!
            This algorithm finds all occurrences of the search string
            in the input.
            
            Each part is copied and added as a new element to the
            output container.
            Thus the result container must be able to hold copies
            of the matches (in a compatible structure like std::string) or
            a reference to it (e.g. using the iterator range class).
            Examples of such a container are \c std::vector<std::string>
            or \c std::list<boost::iterator_range<std::string::iterator>>

            \param Result A container that can hold copies of references to the substrings
            \param Input A container which will be searched.
            \param Search A substring to be searched for.
            \return A reference the result

            \note Prior content of the result will be overwritten.

            \note This function provides the strong exception-safety guarantee
        */
        template< typename SequenceSequenceT, typename Range1T, typename Range2T >
        inline SequenceSequenceT& find_all(
            SequenceSequenceT& Result,
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
            Range1T&& Input,
#else
            Range1T& Input,
#endif
            const Range2T& Search)
        {
            return ::boost::algorithm::iter_find(
                Result,
                Input,
                ::boost::algorithm::first_finder(Search) );        
        }

        //! Find all algorithm ( case insensitive ) 
        /*!
            This algorithm finds all occurrences of the search string
            in the input. 
            Each part is copied and added as a new element to the
            output container. Thus the result container must be able to hold copies
            of the matches (in a compatible structure like std::string) or
            a reference to it (e.g. using the iterator range class).
            Examples of such a container are \c std::vector<std::string>
            or \c std::list<boost::iterator_range<std::string::iterator>>

            Searching is case insensitive.

            \param Result A container that can hold copies of references to the substrings
            \param Input A container which will be searched.
            \param Search A substring to be searched for.
            \param Loc A locale used for case insensitive comparison
            \return A reference the result

            \note Prior content of the result will be overwritten.

            \note This function provides the strong exception-safety guarantee
        */
        template< typename SequenceSequenceT, typename Range1T, typename Range2T >
        inline SequenceSequenceT& ifind_all(
            SequenceSequenceT& Result,
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
            Range1T&& Input,
#else
            Range1T& Input,
#endif
            const Range2T& Search,
            const std::locale& Loc=std::locale() )
        {
            return ::boost::algorithm::iter_find(
                Result,
                Input,
                ::boost::algorithm::first_finder(Search, is_iequal(Loc) ) );        
        }


//  tokenize  -------------------------------------------------------------//

        //! Split algorithm
        /*! 
            Tokenize expression. This function is equivalent to C strtok. Input
            sequence is split into tokens, separated by separators. Separators 
            are given by means of the predicate.

            Each part is copied and added as a new element to the
            output container.
            Thus the result container must be able to hold copies
            of the matches (in a compatible structure like std::string) or
            a reference to it (e.g. using the iterator range class).
            Examples of such a container are \c std::vector<std::string>
            or \c std::list<boost::iterator_range<std::string::iterator>>
    
            \param Result A container that can hold copies of references to the substrings          
            \param Input A container which will be searched.
            \param Pred A predicate to identify separators. This predicate is 
                supposed to return true if a given element is a separator.
            \param eCompress If eCompress argument is set to token_compress_on, adjacent 
                separators are merged together. Otherwise, every two separators
                delimit a token.
            \return A reference the result

            \note Prior content of the result will be overwritten.

            \note This function provides the strong exception-safety guarantee
        */
        template< typename SequenceSequenceT, typename RangeT, typename PredicateT >
        inline SequenceSequenceT& split(
            SequenceSequenceT& Result,
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
            RangeT&& Input,
#else
            RangeT& Input,
#endif
            PredicateT Pred,
            token_compress_mode_type eCompress=token_compress_off )
        {
            return ::boost::algorithm::iter_split(
                Result,
                Input,
                ::boost::algorithm::token_finder( Pred, eCompress ) );         
        }

    } // namespace algorithm

    // pull names to the boost namespace
    using algorithm::find_all;
    using algorithm::ifind_all;
    using algorithm::split;    

} // namespace boost


#endif  // BOOST_STRING_SPLIT_HPP


/* split.hpp
Obdmk4U1UVfYwXfifT0F+u6FZ/kF0ZWF3wAuMyEmHO8q3V4073VXp7DCyTrxOV7AYqdfearFOwSETUKsqpClfPpZQ236G+B7OdpX7+i/VtJuwwuhrMim8gr25t9/L6d/7vtdoTlm2p7H7h46K//RUzFYjBzYthIpzr6/6upM/5muDgQycvyTxgqPA4Pf3wWAgIFDQII+jRX4nj9GQEEhoCGhoX4UeRpWQCCBQ0EiAwUmMYhU9OxiqydQiOXtHSvRKNhFlfSjoh9HD4IKfm/+MHi4cCtVxQkqHEFV3Kusq5iBst1TTkxNXDTIvglRzp3cp/+wtgb8yvEGqVnlpCbNftI5uuiMn/m8T+wMvVQqd1Y7qPOFwbkdNIlz6Wczns2cQzJmCJniYL48wiVXOpvoAbitYbAr35VFfIh3m9mMXC+ODhFBU4ZFORB1MNfdElZJW6q2oMS1VzLXxOiwfCehXExfI7cjhZPM9DTg17EP4P4pFxVrT9mS86ISw3odkycad2sY5Lt2cPuJBDxCF+cgX+D5ptgJxSX7AAXtzY8qSEOiuo7fCx0qoPC6GcNv1t+DMifosBWnnfPBIqUSWCiPuRFAhBpgzs9jT+iiY+m+ZxrEXILFSN+0qcmEfWdkWGKRNgelY2DVCC3DG+4upUUP87wQyJhATrtS40yPCBRs6mbxZA9zPini/0J3ZH9fqsqt9yWhvnHislbrKvOLWpMtWQ58Di11J+VJuuCsP2TpweQnq0JLzxBLxWhvDfypU9FCkVAnYhFtJdMa69VRZE4YY/IXi0dUQbe1Vl8hWkYFPJbKEEcQ/XraRu0eRffxa1oZbQMs+CtaboMmY4c99lWbER7GuyWULFRx73BEsxuiea8cTLeYOWk+HGvpJhrqxRyfxrc4jYPhhJVVhmFoM0ZbXMtjZtsQ7YT1jb18dcUmZ0KfgDZnsZ5Wc4hbQZ36XnBSFEad1fUBiV2VVRFWzV39LzpORmppF0dNiuiFfOv1FJMDG7Zg5Pw+62+rH8e96dXAsZcgmQ/Si7zOdcSTKqyE800a5bkNqhXsrqxk27Zeyxrt6Bwt3Iia7H91mKvUTy8h94peeUQjJqJ7eisekzVhX20fpMGp3Hy4pHry66XejLnjInd+56jBuf2zz9a12aY8PR2HEO6vjI0iElTPkIuV8uRX+BAcCLLfT/WuWIiOu4b5LsIEUsaJ4tQjCFwG1Y8Yrw/C8+iBy6Ugdvd0V8MNrPCZNWQ0EISEhYhbw1RNGAQgHDp4zLxRN8gfRneC0qxHwkB+j6+0eysSDkhbFtYSd4ap+qQXAP8NYHyTG0Nbc7M+krF3qU+8LnlXOHUFCwNCcC7Snd0Upuxemx5EetHaZt6mlTk1AD8C3333UksSN5E7f4ydBQPlBGhHKLenE8j/WIL51EZWZhCseZjH7L3haHpqEt/RGSL2X3k75v+Qt2NkY/tHeTtQULA/PPOABAGHePJ23E8jGzAwKOhnEL8Z2YBDIEEi60E9DmjklSvRMYgF7GImJlHRSBSjoququ5gEFex9O3/v6i5Nd+bjs3GFrOXJJNFgdY80Nc1Mc1Wa+GAgda2EWEwb3k4ixAm+PE9UVU9YrY8/nZI4LOkF1WFm09Ng0RI1gsmVi+ElT9pnxn6ofHuVf/puzSHEgr2qOf4uq37UqXqV+gjn1H8WmHb+oADFEV/tTtNoM4jgUJp2o2q7Gov/owpnd23ygvaQl5xDquXVYHPgXcbFW5NW/ljfUbKSj4NHmqf+KfsmbcrL7Jt4z7SkJiCPnFwKJU1pRW7JVaJt+N2ME3PUu1GoLJeKkJNULpyQLIl2bihqmYtF72aYX0+FkCNP1KtMJte26kyKVASmuFlgf7q0RS3JqHVbHo5Ef1gUgaKyejUIN35ic5hjoYWW0l+4xQj9KRpFMLPkG0DSOUGZXbCvIBB1BhY/C0bCCYGIWkNJsixnqsCAKUtBfDiiAc5YSZKYl7VDypbPkM0AZDKWPNSlon3nfPgd8eczD4U5NES1/mh6YZlKKR4VdCBaqPqlLa6F48i+ESOP/DmpbVXgyL4TkzJrsrcVMQSrUiJ6NZE2hydUhvIogcAO9mE2U2zUh5VSZHNqC6TcsDfK1knBYy+EK21DS6eKssRwLocv0wGDBnnheCYdTJlfzSZqpJLhd67hvvKBOWsl521f86KQWS27mYVq3AXlbzi1LH1v0du20JZs3CHDmX1VXMd9sXGhSOukVsstqJqJc1KxZFzaXtDmhA6R55HG6UdppEi9XGTZVxjPy4ATdAQNDb699828+R0wBoskYupfQBN2sx8D5K0PW4zwCR2WXeS75XcYJcnsdgsRVDan+CHReUe8rD10XgIpliPGhgJ0pH4mWPyhwUF+dr3xZk1ZTJnn4nXBh8rJyWIaav0JplB4RsbJxSTUeMgiNfRmOt32NwycK0d3iuscd+/SjvraqE6Q2j6EWpZl5UmS5C1iitHW7Exlae0mYuFRp7Zm4laefZYJ0ew1NHQs8hDcSrXbGl5QeMbKzMw0DxxwXYyP4TQYIC6rpeg2iEa5oCO3fx8c2jSdjsT2uCOJAdfRY5f1dCQKUormyuNQD+Fw0imNOIi8nsFsozLRFC2mBbJo+o95Saompg3zWCwehfNn4QGa4J+IDz/TsbRqiwXHagbM/6ubIv6VD2P5D92csTIx/6Nuzv744BbscUAGDfKYx/B98gAMBBwaCvBbFwaJhAxFJCCPgkECZNKb/IRGTMasFPuHEdrqyN1qB+Dfb+AuknaR1RJDcStbjcccrZtNDud0oqFACsm3e4rm/acP5C0PYiDt7PGZdRdalpbcwM84lCqshpxWF6zbpyThdYP9t3zBVxdsU5xjakkfLM7Wcz+PeDvEXhSWnt02mL0+U12uMMdUlSIBw9+1mzGST/68MiSRjJDuUVWzrBVSs2nFmGzxmOJn3w8ACDmaUFGgrXTGOWfWXuE3ln/aMJ23bwvWP5eRnBcLcZI4+TjnL0qyxDe00hzjsGZkdc/nyjHzqWibzJGo++vG9brCK3ikr9weEViXrm0pOruKV97E7QUj6Ua8eSxza3Xe5ukl1QQBDhtusBJ5y544kMmfp5xeX3RZpL2ODpW955XPnHCmX52yOzWY8lSrFew/G0OWkyg7Tjxv0OH/KyNl/U8ZKZDln2SkT5MJv7/QgoBBfJ9dIH800kerfAby+xkucDtfZCJiIBOzvF4UCstfzHFBHg7j1DNaL/cvRsadhxfc6Ig/CWzZm57wjxEhcz7VSQnSR2Xbvd8AfAW//RwxH6gfwCpVZ7shYS0mXyVVlcnfWVyobY2bKvzKVmdlY+S45xVemqy50ChbDxf1r493H+AAEJi1btix+jM75vJhqpmFUVzKhkvRzpfDIZPF5Msx9XWGMnHqbBuprZUVX6rjhfQ+mdAGfugaVceRO+wjtRKqx42qRVi2F4JjBKCpquYXKju5ucU9CUOUttXxco+lM7sGdwVH4iYDkmlyYdnMxHINf3lLkPoA4lw+yFMfB2Ypr8JLkjZox636hdBjGLmsZUkFLGhfIydFu6/NNWdSFVK0wbs3/YxmVzqWRPRMVnFjSPZHS/zrEP+lbbL9j2xTWs/R0YhQE0j4+NL+H1mqmL2e61/AL78aKxDI9F8a6+tFA11MCJLnjFU+AJKJPQhW3xeaSaYXXIR+0nFqmynYpIUm7MZEArzN0fQ0YFF7iaxw4bGNGbjE0w6UhHaQ/m5ktt1MSMVpEvJg4DWY4mEM2fIX2XtQlW4GbM/XVMhVWgtgoCkdIlXgSOABgMVIuME/Hxr2v+vQMDMz/zeHJjVe3a+bEFr42FsYVu4Lqb8EQ2UPZlA6LY8c5a6jpL+viP1o15salmgFXKeYAxcPHNCjZ69rhkkaoCGoyJHezYOMoraO8pRS2VYuK/dicb+2wHHzWNkum65lciwkkoMY+UqniPo1Kivx3LPn1lhLG1HsBmk9jm9e+tk1RrA8LybxA2nQeX8o6gnFYj5DEQEdVJtTyTH2qZzI9gNUuvNruDuReSiPwaAKo678Ac4prPQ6V8uT+U0B7paplg8oubaoJi1jCeOQx2JRZw5pKQHrQAarjDCezUyrY8vX/UM3ixtYiNzuBLTPTxc+Mlu0t+ApvtDez5k0IcLyakdslvT/Gr41uE9SNhckCdui5JjLoDJOwF/z0YMpy1EBfqpVmL5KIwu6LskkGZeku0ja/ZOy0q0zHoJq8z0qfrCQ9aFGXHzXNT+kVYsZi5t3WFL+zJ/P+2/gBKHHDEczG2vhx7NESCnMxcTIyAkEMrICH18sHHSMrBSMjBRUP4rZ2BNSEhJ+966EcqY2jjYOpja2hEKKLITSegZm1k9xKgZpG8NfdQEZGdkY2R91sjIy0zGy/NAlZ29j6GRg9Kjsj6qMH/fwq6pfYQrgb2ayFc3cjAiZGBkUbGwcCX8iGtbGNoTAnziHsCaPgBArK6sAq5AQO4soC+ejyMTMzinCwS4kIiTAxCrMwUfIw8wmIMDJxsnCAuRkZRYVYeIAMnMIigCFWIQFBASFWZn4fkJ6agpGxgyqj7bP9GT7P+2Xg/FXS/3xwAjxaezwDQTA8/2SAwKwAYA8XiZAIPwAIJB8ABDoLgAIXAEA5PkuAAR1GgCC9RjHDwSAENEAQEj6ACCk6wAQ8kUACEUY4E8ny8FRz97xtb2RMQyQ8fHCAUNGJiIr+r9s4n/PJjJxMv63bCJ3FS47HE/nR4FKMCxSAZ/+OA6lDTDL9TXe5tiGwXqXGPDghVSKQklauBDZ7JMFnUgdRPxVaO/79u3tz1f8fLtLkd5fQtrqu0pR+Dwo2JLzZcUtMPaypQurxrmUzZtkA4ZNW6k8d9pUuSJvvobM5dZ8Yh/pbZPgckNKdXOjs66sr9SpFxwWmbMoyv40FktdGHcTKGlz2x2+4jyYMVJjs4RRSNmYmi2vQYU/V0kH6WKrUR75fvCTqygzJc9YA5QFUSQ3ErbKijOxmTIOwxiyw37cupPirNWEkvthTRaeNU5wdX9EfJ+p6oLHSlxJ+wqq2kL+NOWsq9jr2lJeHlkGqIBtLPhxoqYe3pLmQ+F+jcLbWHGNY1H2YStARP1Bgt3Upo3xCXHzBnfuwNvpBDjJJdWy3PcDg2/JF5LtdFzToI1ESKPVOUNcp+c9UhcyB1uqY9RzFF6bcJ7hVd1wJUaxxwgUnrxaHetLb+d9SAAELPvTk84YJv/iUOsLW9ibN2YJRo0eiytAjQPSIIlo2/e+kHNysRslGbsz1t2HFazkJVRagwRrKDdr3kEuPK6ZWyI2c5L78lifDlSGG0SBupI41tQwaIGE7Wju2bRT8bTKCAhXlYxjEX0uGu3qoiKJm7ydCu4SkSbAl6ZcIQXSbTy5N1bbKp+l9WU41gjvEc0LOhDBuXcrHMZIYxWzhJUrhoRW6+KqKgxBxPq30mQ0RxwX2ETosdHeUGH38Io+gTCM9aZpn2eVkpmD3ykQMHxAeLGnx9y/K+JqWA7AM3u/d8eNnfsOLLZOxDzcOeUVNf3rfY4JUwwTx97SXuwD6Te2Q3Tk0QaXAxesQIJxrWXn6q00nI9H6yYqC9BqUe7m2nWQIXInoRzsuRViMdgiOQflqkuhy7c+HK+K3s3pi2azGS6v4xN+KxsSNvXpXzoL2BAFJF7ZOXcuG9+0G0FliHwiCmNfkAIGOjJ9qOTCjhEwux2sPUcuoT3aDPnzecImpeB+U8/NnSiy01CP9L5UwD7hl9PEKX5t9A7cs4AOeYyNsAS4oB0KQEtcIi0X8rgsC6mM4Q3K9w+r3KqhkhfMrt+qIaRmLvk2+5IMSto3Nr9ahYLYJ/rZWbuF6v5e+AvzkFhUxDrQwnH1Em486iv0ZIFsU+PsIBlSyRZ4NN5meydqptTW9X4uY80DAaoZbMpp+WYbfqh67q65iGVmNB+twZ0wZTnFrzIQbpgNTSpYtMxs7WF+BZbFzfG+JmEW3f1D6zr7CZvJdPNyHV/Czg0kJ6iL6VM7ZmDGbMUEcGmW/XgH0MED5atp0cerQ8uZOjKUXykQNvBYq2V/MTXrLqp2VEURLFZLw4l5u0JTmXzR9DqE2HCdtR/ONbGcxrT77D2i4QfxePwDo17k+0EgzG7f+35PLcJ41WB/nKrAie0wVEf1g2vbHQ+aVkmgSiozoO898stIz65vbemXHz2NPqlQhWJw58yhRVbbgGl6+yPJyrPTxwxaLB6vCYXafWg2yxSVCVMpH/RqgV54aBWkS9JYLmnEXQ+PPELRC+qs4G0euKTLgQ3P8sKI81hHI5j2w1xQbe1gMrRwlGZctTG/S4vyXxNR0eD1Pxbn7lrAdGTp40jsSXK191tAMa1ISUm81ugKaEk8K6qI22zZbq9Bj2dG4TMdZUDmCbG2V2OTaJkD2V46k0Knb7Ku2zOmebj3uEO8FcD78L/g5f/FrSg78J8MXoL8/uHJL9Abxc9nJ//iYp7AGCQwZCIBcBSgvIJdVOcEsd4f5rFv755ewr9s7+3CYetto4+Amc5HyNq9LPQrXfpCaHPpVL08RaaIB92BNOV8im9dlcYJFkLgVF955GOeFmbwVxRJ7nWm1O9GZOgpxc34c9pM4b3oKqQphrRfzePyTfrsNQGmjL/OAzeHcxmMXXCFtGbcsFrzYkasIRKMXqshOHFL1BHb9F3HBKsT8/DbHZYJIt8s8z2TRKxxsywhMOGZ6VDrcaNhJGXI1bjjz8TJNVgO4MoC9Zvu1/15h5BanWhyVjevHoBvP75MLJZ8Dnmr7YA5sjGQVJMJsKmd+20yTf4K1p5/pd7unwXWpBF9YhkxzPHKjw24iZy4BoJ9bmv2hhuPhwNv33cgoWpHKJmR/oNtES2iwBnQaDyITVc78JOSGr7/lv5QJoJlRzN8V0EFL9SwbxTT84XESCJQbPxmG0LDl2/YjA36XwQGlS31Y6EQwScmnD4nytyvO5tMxCAkk/YxPVT8C0khVzI4JM3QZFxRulgb39g1Kl1Amq3U0fXxQHlCsCzWTmzZf42kZ3C44PQUe4/R+DWlLXsobPle5AJf69X2HkPB6foVv/yPrNTut01DM9Wvli2huo9IjWZflSZdftblo7Ajoa+6sJyrxwE5YUmSJv5lo/gbQVNOTpb/N0FTEDAwEChwsN+BpshA+cdeh8qsZxdFTKLgq5g58VegqRr86etwXfaBdVafVYpgc15aooLzisDsyS7sSE1Mc15LvYKLykCEecbOJUhMbt2eMHTTjnb1bNB747ewF6EHSFJ4b1R1Q9UOiJvBFfr0SAWmikoF/X0soY7E/fOVNQKgAPOIy1FQMkW1MAggFQQN1MvmuUrpgtZwaNasCkWymeyQMPXYhcoU48n+lJGlILVNSJ2xYrM+iyvQa4Mk+y+srN/YGhzxCnv2FUQ2XKCQvwxRVo81qyTyreTuLioZZJl/1zGfuq6sYoRtKa5rKXNiuXg7mKmsZMA+BvxLkfFl80xdHKFN2FIJCv2FVa44zvrlPvhQq6aZAuR1a9NIdizdDZBk0Qo302YgBH/KdBPW66X4ZWxsbIh0rTme0nx33mItQpGlvqKVRpAyG7N2F5HByfCcbbDanQPrMjE6P+5AVK77YkY1fCzs0tJ9DInk
*/