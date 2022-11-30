/*=============================================================================
    Copyright (c) 2003 Giovanni Bajo
    Copyright (c) 2003 Thomas Witt
    Copyright (c) 2003 Hartmut Kaiser
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

///////////////////////////////////////////////////////////////////////////////
//
//  File Iterator structure
//
//  The new structure is designed on layers. The top class (used by the user)
//  is file_iterator, which implements a full random access iterator through
//  the file, and some specific member functions (constructor that opens
//  the file, make_end() to generate the end iterator, operator bool to check
//  if the file was opened correctly).
//
//  file_iterator implements the random access iterator interface by the means
//  of boost::iterator_adaptor, that is inhering an object created with it.
//  iterator_adaptor gets a low-level file iterator implementation (with just
//  a few member functions) and a policy (that basically describes to it how
//  the low-level file iterator interface is). The advantage is that
//  with boost::iterator_adaptor only 5 functions are needed to implement
//  a fully conformant random access iterator, instead of dozens of functions
//  and operators.
//
//  There are two low-level file iterators implemented in this module. The
//  first (std_file_iterator) uses cstdio stream functions (fopen/fread), which
//  support full buffering, and is available everywhere (it's standard C++).
//  The second (mmap_file_iterator) is currently available only on Windows
//  platforms, and uses memory mapped files, which gives a decent speed boost.
//
///////////////////////////////////////////////////////////////////////////////
//
//  TODO LIST:
//
//  - In the Win32 mmap iterator, we could check if keeping a handle to the
//    opened file is really required. If it's not, we can just store the file
//    length (for make_end()) and save performance. Notice that this should be
//    tested under different Windows versions, the behaviour might change.
//  - Add some error support (by the means of some exceptions) in case of
//    low-level I/O failure.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_SPIRIT_FILE_ITERATOR_HPP
#define BOOST_SPIRIT_FILE_ITERATOR_HPP

#include <string>
#include <boost/config.hpp>
#include <boost/iterator_adaptors.hpp>
#include <boost/spirit/home/classic/namespace.hpp>
#include <boost/spirit/home/classic/core/safe_bool.hpp>

#include <boost/spirit/home/classic/iterator/file_iterator_fwd.hpp>

#if !defined(BOOST_SPIRIT_FILEITERATOR_STD)
#  if (defined(WIN32) || defined(_WIN32) || defined(__WIN32__)) \
      && !defined(BOOST_DISABLE_WIN32)
#    define BOOST_SPIRIT_FILEITERATOR_WINDOWS
#  elif defined(BOOST_HAS_UNISTD_H)
extern "C"
{
#    include <unistd.h>
}
#    ifdef _POSIX_MAPPED_FILES
#      define BOOST_SPIRIT_FILEITERATOR_POSIX
#    endif // _POSIX_MAPPED_FILES
#  endif // BOOST_HAS_UNISTD_H

#  if !defined(BOOST_SPIRIT_FILEITERATOR_WINDOWS) && \
      !defined(BOOST_SPIRIT_FILEITERATOR_POSIX)
#    define BOOST_SPIRIT_FILEITERATOR_STD
#  endif
#endif // BOOST_SPIRIT_FILEITERATOR_STD

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

template <
    typename CharT = char,
    typename BaseIterator =
#ifdef BOOST_SPIRIT_FILEITERATOR_STD
        fileiter_impl::std_file_iterator<CharT>
#else
        fileiter_impl::mmap_file_iterator<CharT>
#endif
> class file_iterator;

///////////////////////////////////////////////////////////////////////////////
namespace fileiter_impl {

    /////////////////////////////////////////////////////////////////////////
    //
    //  file_iter_generator
    //
    //  Template meta-function to invoke boost::iterator_adaptor
    //  NOTE: This cannot be moved into the implementation file because of
    //  a bug of MSVC 7.0 and previous versions (base classes types are
    //  looked up at compilation time, not instantion types, and
    //  file_iterator would break).
    //
    /////////////////////////////////////////////////////////////////////////

#if !defined(BOOST_ITERATOR_ADAPTORS_VERSION) || \
     BOOST_ITERATOR_ADAPTORS_VERSION < 0x0200
#error "Please use at least Boost V1.31.0 while compiling the file_iterator class!"
#else // BOOST_ITERATOR_ADAPTORS_VERSION < 0x0200

    template <typename CharT, typename BaseIteratorT>
    struct file_iter_generator
    {
    public:
        typedef BaseIteratorT adapted_t;
        typedef typename adapted_t::value_type value_type;

        typedef boost::iterator_adaptor <
            file_iterator<CharT, BaseIteratorT>,
            adapted_t,
            value_type const,
            std::random_access_iterator_tag,
            boost::use_default,
            std::ptrdiff_t
        > type;
    };

#endif // BOOST_ITERATOR_ADAPTORS_VERSION < 0x0200

///////////////////////////////////////////////////////////////////////////////
} /* namespace impl */


///////////////////////////////////////////////////////////////////////////////
//
//  file_iterator
//
//  Iterates through an opened file.
//
//  The main iterator interface is implemented by the iterator_adaptors
//  library, which wraps a conforming iterator interface around the
//  impl::BaseIterator class. This class merely derives the iterator_adaptors
//  generated class to implement the custom constructors and make_end()
//  member function.
//
///////////////////////////////////////////////////////////////////////////////

template<typename CharT, typename BaseIteratorT>
class file_iterator
    : public fileiter_impl::file_iter_generator<CharT, BaseIteratorT>::type,
      public safe_bool<file_iterator<CharT, BaseIteratorT> >
{
private:
    typedef typename
        fileiter_impl::file_iter_generator<CharT, BaseIteratorT>::type
        base_t;
    typedef typename
        fileiter_impl::file_iter_generator<CharT, BaseIteratorT>::adapted_t
        adapted_t;

public:
    file_iterator()
    {}

    file_iterator(std::string const& fileName)
    :   base_t(adapted_t(fileName))
    {}

    file_iterator(const base_t& iter)
    :   base_t(iter)
    {}

    inline file_iterator& operator=(const base_t& iter);
    file_iterator make_end(void);

    // operator bool. This borrows a trick from boost::shared_ptr to avoid
    //   to interfere with arithmetic operations.
    bool operator_bool(void) const
    { return this->base(); }

private:
    friend class ::boost::iterator_core_access;

    typename base_t::reference dereference() const
    {
        return this->base_reference().get_cur_char();
    }

    void increment()
    {
        this->base_reference().next_char();
    }

    void decrement()
    {
        this->base_reference().prev_char();
    }

    void advance(typename base_t::difference_type n)
    {
        this->base_reference().advance(n);
    }

    template <
        typename OtherDerivedT, typename OtherIteratorT,
        typename V, typename C, typename R, typename D
    >
    typename base_t::difference_type distance_to(
        iterator_adaptor<OtherDerivedT, OtherIteratorT, V, C, R, D>
        const &x) const
    {
        return x.base().distance(this->base_reference());
    }
};

///////////////////////////////////////////////////////////////////////////////
BOOST_SPIRIT_CLASSIC_NAMESPACE_END

}} /* namespace BOOST_SPIRIT_CLASSIC_NS */

///////////////////////////////////////////////////////////////////////////////
#include <boost/spirit/home/classic/iterator/impl/file_iterator.ipp> /* implementation */

#endif /* BOOST_SPIRIT_FILE_ITERATOR_HPP */


/* file_iterator.hpp
7IzeUWbMr7fRiObRR+QbeIhGhKfky79vH8TyHOBFDDwX8xPpRQx81eM8T/+NZtedvuUT8OysM9K9wc5E6fZ43MBvtDMRPtmEz7QzEb5isoHPsjMR/owJr7UzEf6oFg/pqerp2hB/UQtPuJ4u4U9WGbgeP+HbJvvvP/31f9STGnYL8iqclaZvYANkgwZ4dO0Z7bVpMPwJ8LVpgPfiNR2Pl1eDj1+o+MtioBzDnwi/UERH6xdK77NkfoHM9g50PzFbcEzw3+wXqA7rtxrrN/mplq3fYP0AUf026QdoJTTpB2jfvkjxm/wAzcD3OBn9AH21ivu24+UHaNcTPF6R1S/5ATpwKBJ+wzCXhXQQfoC6ruD8EG3Ga7IHmusqryoTXnoUJeP8aJitGHOlPvaWUeZkTfWUVVaW2h3uxgZEdyE/HUAZMnENBLQfetOalh2Pn8j5s9P2Q0/bDz1ZxuOUdrD2Q8mGb/Yfo+FmvYFrB40LO65pep7e4gJHqcV4sq8w5MZ+Xx2bVzHEq3wmBdtaUrId+ckzVwtlWzy/SqRdE5awdMYXIzv2Scr9d8/2CWnDedx/021tRftatJCO5SPnD+f937dtDLxu+OnG4OTNm09DI3mzFLGjlTcnQs/heO3/bvMewI1v8ZpY7cXR0u+UxzfKv4NC35F/B9Wuk39/dXoB/NsDkKy3rX8JpPoWuS/I9S2mIa5a5rG6Ic1DvKMFp/ArXvD/PSX7jiM/ZrJ1vq4bm25PiVOrPZXlwqdroz1Vm3tHQ1IIt636TY311/ZjOxj+Pn43bQ2svxb/SXDtoKX63ePdDnT9Ndjc+vprT29uvv7aO301/TXkuRQ7k9Cr/kj73kQ83c5E+JQtBp5sZ7KGT7IzWfFUO5M1njQ7kw+Ox2g7E+FvvG/g0TYmwis/ZDzcgq/Y1DSfs9kst1PG6ev6RUMvjc+3f9KYz9Muj4ERnwTH5zs+OzX5vM/W1ufzgq3N5/PVAww9zQw7E/FJxKcGX2XamcT+AQ0Pt4QnvtJxc3jCZf3I8s8CyFviP8sgJmFgNGxW/I5hlMeQ/xow3uJtgfmv/Y7jy3+t7V/s5e3QaLwxYFtjvcqzEQuG//yNN3T/YvMxPfIvABMs7NNGftoODoqW1vHB7f7ruMse/NNLUbrTGQe4XemMHXk3OqOs+gXr8kKsI7LoHafkKen4N1WpVDxiH3WhiOPvbVZn//abqqSNiIGndgMUCrvw5YpTKVOKhA1gWtlyKuTLtkrsIi8Us8+TMPw/cVxq/zLwuPTtr4LjkyO7G49Lg+GT1pZTRzMu3X8M49K59CyW3ae7uUxJPun6bDRO7TVEPk4t+VI+nnN85Z+XyM9mzRBNjoX52jPYvMf/c88iH9SijHx9b2B5MWpvcHzQXHlxovjgwT1Gf9UafoWpvzq8h/srsx0Rqo/IkawXv2pf4Ha5c9+pWR/mdrl7X8vrxVPbe+zSaOm31+Z9/tuK1W5znJKr+fyIE6seTjxnKQXKtcIvhUesgejPmMOSpw7ysEZWMOggGU0WL3RvJ+MkGB26l4047A/If4hbyPI4YR+kWtgDKRHeTHR/Gea8+Aslj5Ps0JcLHyLORnfM95xaCHNKvunq8XN+pou1IbcJzRSlUKJM0+J2Iv/H/giwEs9LDgGs/Qkgr6K0onJ6RZyrptAltgBjuNdM9+m5wuryem2oJg76TI4L/2us/jutS0dJvX7LG6nxPEjz76qfrcdv1g94PmoTK93JNSVkhqTQVY0VXi7KmMrWhf/6in6YFrhyXJ7cYrfL4cSPi8LS1KkOt6PC4+J3No5A+fn2VT73T9SAWv1szd+yjFhQRsdCmpKmDBMjgmGK7kvGqf3rjTU3WvsX50VmaP8UgfcTeD8NIT1U9ili085Jop5dGkcw32Xi+0+zYFmabRgdYb83Hp9QNuSyIqRqhdvFFXhdpqVL1/q6uQ2fdIv2QXl0CM4kfzYpeL8Af00VmP4ctUwD4fzqedTzpedHz4Oetp4upzND0dPW09XT1NOheIifqbU4tScoDOXW+J2LuaUQ1SZsnGhJvHKqo7kYyvx7tPB8YzyTI/Jm/s0ShdPT09Hj1uP7f/a+Ay6K4+1/KCooKqJi17VjAVGxRBeWLhqaFLFF2Ltb4OS4u1yhaSJ2jWKwRqzYsUQxdmM87F2xY4vYNZqImqix8T4zu3fcrpLk83s///f9fz5v5nz8Tn3mmWeemZ1ZdmfNfMzlYWyE9ElN7aMnxqEA15kKA0dhTyY4FBbWRaHokkkqiYRu9wvD3+CWc6ky/s8q4Zo0iz9CbtBgbzSMVHOknzHJqAfBBhhVhMcAI3l0GvlpdUrSh6xOTvqPk+lgYPB5WDXxQj2YP+aLeWJemA/mAeUyMQ9cHpfFZVA0azDqFCzhEaxTEl9MslGnF+LiOIWaEwIxRt4XplGTiGijgKwBl8XlcH6cD+fB6ShYpQ/WwbgFhCE9iFUZib+fld9PpSKfuEOhAfEx/cOCMIbHhgVF9Q8gcWER4UExflFDsD8gZkhkkJA3ICI01C8miPj9QvlPBSDal38+BF+3PME/52xDcg1rY/bLXJwbCv4+8S7OToI/dLiLs73gTxzmAutMO/sqVas5OFav4VSzVm3nOi5169V3bdCwUeMmTZs1b0G1bNW6Tdt27d06dOzU2d2ji2fXbt29evTs1fuzPn1pbx/G188/IDAouF9I/wGfh4aFR0QOjIqOiR0UN3jI0GHDvxgRn8DK5AouMSlZOTJFlarWaL/U6Q3GtPSMzKxRo7/6egyK9+gMuxGE+iL+3UU8gXlDQEdsEF8B8FWOIjOBjsyfFGl/DPmGSTTZAVWk1UT4HFjzd4A+TsHjnP9GDc7xqfQo1BN5ou7wwzHukMePPAeI5yM8L1FktqLIbITlCiO1hYIPz+4KEpdIeKaSvHhHhp/vYcksy89qeO7C8yoe6/zzhRT8X3G9s+aF05UkBZ8EpkRZQj48UquTkczz53dzeE3Bf2OMr5OC2oyEP07Hczh/xcZp+OQslaUEz9EDUvqTVvJcUyFWT8I4ZwriBNlxu7B0/JfI8IyI82ig5RThpyL5+ZaxpGazntwRvxPVCusYvEpwg+uIHEI61IFoj/8SmVkma33iFn2sKTXiv01rFK4luH38/xUlA4lM5u+UeXzU390s/a1GGtIajviw9vAqTU++xsavqxIF7vgLZHxrzT3Fp/ArOF56aT1d/8auPu5vDlXoG3+vJkboF50lhdcwrg3L5/H/xC6k7fC0tMMsk1lvn2qBQlK+G+ptKY972/wFvr/WAtYBls/My5pfr/+w/9JJC/96nH2qvp7/QX3YShX/YX09LPVpSU9hvmmQX4fwqgLz+NTIMY/FCo5mfl7/gfzxhCverWDJuwgWxYdwz5l78WP5u6LP/rK/8Xl+nCAxP575s/4oMgvidsor4Su2IywN5iQnkuG5xWwzn5rrrflU2M+n+aQKsxxuazLRP0vi+Tkg5W/5/yf2Iq5JQfTNCtzNfCvGIdYpLmeA+RTPo3hewKMdr6LNujV/bVE6Hj2t+uefy4dz8DaI+yyVhA0i+Tyt+uef88UraLzeN3PUf2S/nlbzdSLpA3708FccLYSVpCTmj7+nqUW8Ziqk4Mvw+1Tr/sK33Xz78/cAHoa4OjsC5gLiHCGAeNFV1s/VuQ6OB3TB8YD476dlwa7O+O+62YB4g+kJiJ/HLQpydW4CGAmIv9uOAPG7e0WBruTvsK8DXMnzubmALQHz/Vyd8XsE2YB4PaoAzML1AL7DfLvXc8a3+d0gHEbGBu4BPGYSSdsGISVpNz8rBKBO8KNAc+IVFd5r411RxZ6ouqAHmuxl+C+NsuTqqUb83QZ+dKQQLeI9uw/JL+UcZBkJLQnPiu+WYi59EG6rG8K7L2yNHQgPN7VRpQJvVfzPBn+Dxq4qqmrrbB8UFFQFux6e/LuOblTvyMHVHFAvT8+4SNjcUhS5XeOQkJwADqEMbQY4B8iBqiEHBwd8hL8Dqma+p1M1O3tS9thsqMBuUvakcdn1qlSBGiZOnFgF9OqZHZk9BXK7te8dGZcN5aGSyEj8SBnllj0lG0ohqCY5OdnBoVqGVpuu1Yr4y+GHN0v423vBYJu9rfx4BjB/6xF/NZT/tiH/vUHsoPqiGoK/GfjN2/t5Vv4c8JvbMcPK/62VP9fKP9PKP8vKP9vKv9W2wr/Nyo/vkxDbR/y3zcz3WqKMaoMylaMC8GvKVJBOp9FVx8+kk9sXVCqXqtFlUqxOA1smKp7FOx6WSmf1lFyj0xlh66eA3H4UjlZRaaxOiT/nTTIY9ZyCknGJGh1HKQ0kSqlWGpSsSplFSknqkDIVnB8lZ/UGyqChWEqfCgJwOkrBGljKkKnlqGRciCVVsSCEXk9pEkmyB0X1T6QMyUq9ULOBU+M7SqwK9roaI6VP1hhVCiqV1adALo7Sa4w6OYdL4xCpMl1pSCYhVqvVaWALyxo4SqY04DLAPlijo7gMNlWr4vpQVPWajvJkVkfJKW/KTUm1ozwzgoM79K1eMyCZVScp1Uk8X40ClKE2ywWNVqpUlFpjoNjERE5uIJm+NIKKDJlmWXSc3qgyYA4aLfQUVh7h48HrKAaypOEdKc4fFB1Jmos5asnfE1WZlJ5Nw+qR67B6WCrRqJZjTUAjVSpoRwyWRYn7C+qF7KxQI+aHs+CarUopOLkKf/CFV49GzVkyyTXqNF7JfJpVIa0Gd4BOUpilFEpotg4KfYKJ0L7scFfnhDBXZxrIHqgk1NV5J5CNYB82EuJtSjBYA1GOYJTtUXuxkXlU6M+SBfKALmQcloWYFZZUYzQIUVYWDKVh7LjHVAyeYFapMoK1t26roNyptnrLGAvTKIzAPZxN5Sxx+IM5ahwhOH7OdYfZxTzrVnz3GN9JxvsclWWl2Jq8dUaR62VbxN9/Fs/Z1qUr5m+8l6iJ8N8YP16zKchVhv/bId4T4l1AAMI7Pf7r1Pg0arwbkejYPClY1IpQqHg2EM0EZgWywv1d0Rwg8MApAcKoN495MtzxUMfdYD3SLTzMRmbFBNyEga7Og4F8geoB/R7p6ux0pY6zk28DZ9fLdch9ZRmrEN1zjhlK7hGFadQxRi6OU8QkG4N1Sny3iNyvCuZkYazOT6sLYzMHGNUDjCo/Y1I0p42QG8I1afhGFjiuk6cnfteknLjaFiSu6Bp//xfQ+TWO/9bfjAjf4y0vH2PBjKWRdQPPM4O3uLTo+rSFNxIcz6/CmeN5V3F/WRxvdub7ymYsE8qXjeHHVQX+efq7w/Wm9vD1HttB4TjboSh2Qo+R2cfaFp3rMe+67ch3zKu8hl8vXe/q22Nz+vXnWc9NDn4eJlXW0Erqxe5u9QK70UyTVwPde1fxgfb8vH1x3DSmiufbD44pvb1R9ryfN2rnMM1uzXTKePcZpPvM8Li6gGmsVS8526SHNyoa8qrk+3xmGVzOBnZsAunyw6/erGCYP8Y+k/V0gPSnQ5o3WMNciznDNP7JFdKP2Ob6rGMmnS8+GneupTfyPeDevdv3TIvAK6+vZUH5/EvaOm6FTFrkJrdpLyCc8OxJi0WbmQux0c2ZUpCviHvfpP4WZm7SdPvs270g/VB2+9lbmRerZKc2HOwC8j4aoa+ynVn61bLWZw40AH4DctJTdjBZ6nyXh3ZNofzd8BqXdjLjQsNP3kPQHt82rbZ23830iEvy0j7rCeXXxGyf+yNzJDytzYhaHbxR6SPbdr/sYU6c8BjX4exjGuWr9m3138s8Cst5UfteW6h/5OYqOSZmTfqO5atmdPRGFH1oYWoRE/Tm1m85Y7thfW7wqbmP2Vg2/kTQN829UbGhPrNzH3OhfPazRjVsIBxR5cPA/UxRupuv44YPNCr9vannq/2Mn7xxzSN/eHqjyMza2jkHGIWucSbzCOwtf2u0ocNBxuvzPYccT2N9fHjT5vhBZmDyff8AysMbeTq6GGWHGPcG67Y8uQnl0cvGjZ8fYuqyPu5NnjIQznVdnnOYKc6b967znF9pWPCpBlNHmFMxvrICyhvqa1o+d+sR5lD3mcmdbaB9+acTlzNHmaWtJ0/ad5jyRmWDnGqdPMrczD+zbOsd0Ffxg6c3hxxj7pWWZ9lSbUCec/1aPDrGUG2eq2p1B/vwtZu2Un2cGTOs064Nj7tD+ahDO9AJRr9OEar8HerT/jn6/pQTjC4/o1XrctCXr8fuO1VPMqN/ij1V/wTWn+rC4pknGd2G+3OCt9fyRrl12bd1TjE15m2cec2rsTdyfr9+yNJTjF51eU/rUSBfwtdR3q6nmbuzPZ4rF3cF+W2vd15wmpn8bGzuH48hPXdO2uAWZxiU2+CXx5uqQf3XWmTnnWGS5z1/9ZW+FbTHMWhY9WJmTNvo1sNSQN8P3/bKDilmDrvs2jV7JNhjQctBXScXMxtfmL66yoJ8O0c2+/JwMdNtn2fOgEfQ3oJzp66UFzPZi5+9rNUD7D1j/94uvmeZabtb+VM0yJOrbPRd1lkmb7h7y8znYP+DN3hmbTvLfD2hXOZzBvSxs0/9a2VnmZu1nFp7DG7vjUL8I2q1O8f82WKlm/PX9YFfndUy2TnGpZGTR+NCF29UElD05fxzTGavJRuUn3UC+62Rtu/iOcbkUHvvz7/0AXv4cc0Wp/NMt5LtjfJmwXj+1PxlNf8RHCjGsodXRViaLcaiFmLM33tFhNlfiDHSTozU2hIRlsaK0a38sggTNolxfrwYi2uLMfvAJREWZImxuKsYtU8uitB5jRjdODH6thZj8d0LIkxYLcbkFDG+7izGjD/OizB7txjReDG+DhdjRgMxau+cE2HpD2Is+VqMIeFi3NlMjPlgn9Y45YAYtfPEOFgpxp2MGPNdxIgeFYuwZL8Ye+eJ0VkvRm1/MRa1E+N8JMbSrWdEmK0RI9VRjEV3T4swYakY0VAx5jYRo+elUyIs+k6MkUPEWNpYjAl3ToqwbKUYtaliRF3EmP3qhAhRkQTxWmeMxVd+fc3lXRMTv9xc05ePKi+v6fuqZ4DT/EYv574XSpQydlyGlveDs6mHZn6o45xj4+I8C2hfueQpgKLy8h77k1suv1r7WLnAoYxxsHdwwITsnXiyuDJmjK05v48vv8J6KkhoZjy/SEBfoYy5BVbOHGdeX5UKYUqaMRv+jcGNB1HHYHHN8cef9/8S6FmC//KaQDlDXrze30K9ykbAsQZWjeQaWJ8r1ShVo0jEhRJVGg3+e6ycI392RSzOBA4U1hWvSVlcACMuBE6lScJE0rBStZp0i2DmdasZawvrVDNCm7BnjAV7v/ng73Gf8Uw6Mjvuhcf/+Ho19lBNx/n99zN1m1NQyxmT8auLYYdiD5nWxGJ3kYnOmjQ/L+8YQ+7boVKTwEdc/7inYnSQ4KzfxNhcght/FaO/BEueiFEnwVoS3PBYjOESfP6LGOdL0F+CTx6JcYEEQyT45qEYN0hQJsGGEix+IMZvJBgsQVsJ7r8vxnES9JdgVQkevyfGGRIcJMHmErx/V4yFEsySYLAE60nw9h0x/iDBcRKMkmAbCb68LcbjElwiQYMEB0iQkuDrW2IslmCBBMdJcLgEe0rQRYJPSsV4XIKrJThBgjIJ+kuQkiCSorWjNxfs/Zap
*/