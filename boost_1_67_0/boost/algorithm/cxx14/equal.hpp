/* 
   Copyright (c) Marshall Clow 2008-2012.

   Distributed under the Boost Software License, Version 1.0. (See accompanying
   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

/// \file  equal.hpp
/// \brief Test ranges to if they are equal
/// \author Marshall Clow

#ifndef BOOST_ALGORITHM_EQUAL_HPP
#define BOOST_ALGORITHM_EQUAL_HPP

#include <iterator>

#include <boost/config.hpp>

namespace boost { namespace algorithm {

namespace detail {

    template <class T1, class T2>
    struct eq {
        BOOST_CONSTEXPR bool operator () ( const T1& v1, const T2& v2 ) const { return v1 == v2 ;}
        };
    
    template <class RandomAccessIterator1, class RandomAccessIterator2, class BinaryPredicate>
    BOOST_CXX14_CONSTEXPR
    bool equal ( RandomAccessIterator1 first1, RandomAccessIterator1 last1, 
                 RandomAccessIterator2 first2, RandomAccessIterator2 last2, BinaryPredicate pred,
                 std::random_access_iterator_tag, std::random_access_iterator_tag )
    {
    //  Random-access iterators let is check the sizes in constant time
        if ( std::distance ( first1, last1 ) != std::distance ( first2, last2 ))
            return false;

    //  std::equal
        for (; first1 != last1; ++first1, ++first2)
            if (!pred(*first1, *first2))
                return false;
        return true;
    }

    template <class InputIterator1, class InputIterator2, class BinaryPredicate>
    BOOST_CXX14_CONSTEXPR
    bool equal ( InputIterator1 first1, InputIterator1 last1, 
                 InputIterator2 first2, InputIterator2 last2, BinaryPredicate pred,
                 std::input_iterator_tag, std::input_iterator_tag )
    {
    for (; first1 != last1 && first2 != last2; ++first1, ++first2 )
        if ( !pred(*first1, *first2 ))
            return false;

    return first1 == last1 && first2 == last2;
    }
}

/// \fn equal ( InputIterator1 first1, InputIterator1 last1, 
///             InputIterator2 first2, InputIterator2 last2,
///             BinaryPredicate pred )
/// \return true if all elements in the two ranges are equal
/// 
/// \param first1    The start of the first range.
/// \param last1     One past the end of the first range.
/// \param first2    The start of the second range.
/// \param last2     One past the end of the second range.
/// \param pred      A predicate for comparing the elements of the ranges
template <class InputIterator1, class InputIterator2, class BinaryPredicate>
BOOST_CXX14_CONSTEXPR
bool equal ( InputIterator1 first1, InputIterator1 last1, 
             InputIterator2 first2, InputIterator2 last2, BinaryPredicate pred )
{
    return boost::algorithm::detail::equal ( 
        first1, last1, first2, last2, pred,
        typename std::iterator_traits<InputIterator1>::iterator_category (),
        typename std::iterator_traits<InputIterator2>::iterator_category ());
}

/// \fn equal ( InputIterator1 first1, InputIterator1 last1, 
///             InputIterator2 first2, InputIterator2 last2 )
/// \return true if all elements in the two ranges are equal
/// 
/// \param first1    The start of the first range.
/// \param last1     One past the end of the first range.
/// \param first2    The start of the second range.
/// \param last2     One past the end of the second range.
template <class InputIterator1, class InputIterator2>
BOOST_CXX14_CONSTEXPR
bool equal ( InputIterator1 first1, InputIterator1 last1, 
             InputIterator2 first2, InputIterator2 last2 )
{
    return boost::algorithm::detail::equal (
        first1, last1, first2, last2,
        boost::algorithm::detail::eq<
            typename std::iterator_traits<InputIterator1>::value_type,
            typename std::iterator_traits<InputIterator2>::value_type> (),
        typename std::iterator_traits<InputIterator1>::iterator_category (),
        typename std::iterator_traits<InputIterator2>::iterator_category ());
}

//  There are already range-based versions of these.

}} // namespace boost and algorithm

#endif // BOOST_ALGORITHM_EQUAL_HPP

/* equal.hpp
+XYuznxk8SDgIa81BVh3WmrhJP6y4lMEdWHSzN0R74kKChS8Hz/iCrAgrsaV7eUlSOMK3Lh8NwrIZuYUa6rX9YpYU9l0mD1JnqzUOfWlCjmqNDTjQahUld3SWl/X3u2+pSe0Z0PWHnvuFb6lH7SqvN/IvPtS5y95pTjsHopa1Rerwpubam5ZHYOKyS3Au70WLzh1S03HiI1MVsY20vlvwUf+VNrUIJMfNYYQtq73m7W+l/FYY6kq4yrraD55VGM8aoUcH2jTrBndtUac9Rr1vr5GLZ/kbtJlXdoyDPdaDA9cN6bT0+3Q15ukJy93lXkos3gir5EzmqzD8aUlPebGtCe+MSoQu6Rfa5pHUzKtXUh/2uwFJ5FECdOmS4hpGV5aUleKpzNsIiX2Bz8SmlWdPmJYqNR1U944zllcI95aT7pobd6jc8eKqSNV/fmWuaYH3tE7qO/quhaN+agV+vyM5vz4T+8ZyIP1xWEiW6KBoHrW/aRvZv5oLFScLjdX5URxwH3PK2XKoWi4nl9NhcxXGQMESs3hCE9jcw/UAYWNI/TnOl4XP9sKiKEyrjjCPwkZfbzCTrcJpkEPiehO4uPuqf1dOPuXzauQGnnTvsamSG4VLvFUzCaVKr04Pw+IAP/4MA49cXSHRY4qOH3sO74/KeoTAfR0eHRxLNrV5gvE78vgkMFDfFNazKnZ/nUwVxCra8Oi2mk+K9zakVGs4uvZONknO0Bh5umJFM6mRfUSZZ1A+cZzz3tOj3+K1KD9Jh9j3mK6lQXRL3o9zXuWEEXuqiXSCb7vgFOyDHcnmYEUYlWZkfj6Io/+8ebs6+vLy1+SDIt4PuFiOnjEgVewkAZ4FJYh7JC7fnxtHOSBTYp1geyISIQVsvwRLlIimcYdSF1uivkVllhh/S4pVSMOagTKRMoHBzWkFzllUvzj1rJXFLw65/tI7uMESTW/Jyk8J6eB5KERgS1X45PgJOhr4c5zwNOG5j06ejAqEQr/xE5oNIDJzWMslBWJaJFl4PXOsdPvfXYSE80LDlSkR5Ry+jySEb/Jp+mCTxY8F2xeeXHeirm4/S5hVeyLI5BTm0NVaGhT+6z8p2U7zmpCej2ntS0k6yMa3dH/b1OHcwIBOV3oIXWlxNu1EbFQPh2VowGQOsQuiCkB5LapMZAKNTeidDBtWlVY3KjE7XhBRdPWEGbZ7nBSkyZcLiGz9rEeRKSJ4cdLoln42M6NfHV894W89SPa7Z/rv5gMiyKr8VdU//ClqyX/FgoiKmPcLDGbJ6THhXaH8I8l0xRi/YOL5P8nHNNlLY7XkJi49lLhVCgA4HtQmTGRAL84cLlB09gSQyCzwYK49P5UWgU9Jr8x0Onj55T0vgPrmxQ44nuJNUhMfTEujNOYtLrc+SamHZXCXUunJ7ahsp9jaqgM2u3a3xr5c5r1d3ZbAszGLc58m00XfPnYbyBKEGbzPBbxA2A0XcQ9fbcNWH0WTbdQcpwjWzNRb5BJtJlNfz5wx2THeaGjLrZn58FBwC/NwJpJSF18Vkr6eKlDB40ij1RjPXpyuQi/tDk9h/FAoscIymIwpUGQm7D3Jl46y9tud5T0JDv6SCSmpzdfSzHtxhC0EXkDS4E545aXBCvwxCgqqmDSARmr+KsiUTMiHa/WGuhtLjEPJQZPR6d85MOTvj4EC14ZF6R+/y9Zqg3Z+2aPuUZcwVOYUzz7BlFyL9DyxNDAfa9YM2MTE2MjAzR9U0NkJGPTHBNEJD0DRAM9JFNTeGM99FzTPZJ9FBT04iJ0U2Q9A3RUY2QjI0MDNBM9H3H9QOFUoHQh9Y9duWq9EACCOyLAqQgjAEQLKEBwMByA4CAYgMEBoD9EPiC/MCpAfhoeAMGCEwAC6ESr2W5vseaZBkf6t1Tzt1yFqqlnrJ9Yc6UDT1Rme6dmb1RmazDvxD/5XMCGDdNlqZBkz7aPoHs/BhstWoldMpSxjA64F8sHy6Y7oA6hl+Mjn+2719f95tXtSNnVgWTYAUP1Ernx/p2pYhiYB38CjOMSQ4S9g6YKDiHleaEs9ulPytOxCUflmvTFh6Omijf5mY1UcsM6FZjitKWcq8CDOXZs9tH7MbW/ZIuibDJcEjoJ8Tey8jn62cDTzXDTVN2qX+EPjTMcSsiWZtYkTyEXbxlecEzGYuquDLPsNBZf4mVmV6mqDXMMubtoGpDFRbvzCu42wVfYZFabDlrATi3oh/AuDWLkO8kGJnZxbDzYhyub1ewQNS4rDG0At7ghUBYb9F7/ASiA138ma5mhEi8VXGwqZnavKThL2N9sNOa46Km2QdMYxvcpyKV7mpdbqZdQW0u2f7oqP9cvYsxJKhulGGcamD8OhXMQjpIRQdQQirLr46qub42Xp3qmJpOfXc1erg/1ofyaIh9WaEHeFRWMGCcA6UlLjKMkjJNoJcWu3nRkc5jg4/jShBXEF/q34xxCBmVoveCJa6VGu1QBh9NopA77NDZzErWQGZTlhczMzJQ35jhKamJjRjv5VXiL1NAB1g9OFEB2AHVUYNeog1aOVi/Xx8FVLR1t+gm3vtCUZZcsLGDNGP2XdlKz5EHV53TpcKhC3mm2xhShYwpBQMzgvpzOZig92cuioYWbnekzKkY5ke6rhiCUqIWZZJcn7jcIDpdDUBPPbX/FAyrRFEE6Lj7s347sILeFd8uF1iyAoGTMdJXxqcmKooFAcuBUNFho6lMjuWRJI0aNsq0+A4dq+qp12LlpomYaj0Pv2Nyl2xkxFBfI8jXmcqcTsZ5JDKLxSzYY62EiJjZv90watDsThM+J3QjNauvBMhnfjk/IxnkNRgrpm44bo2nMqkExrlb2hYRHPpEB8ZHeWnLeqsY3rxwoiJs40aQEHC/L61vyi2v6aKLY8tfP7uZdGZQw5V+p7KB8TjZojUnb9Tn6uquEMtZfGw7agD0kL1pODZbQZ+ylStzVKBp75lst0jYMyH1jDD+LgxKWFtYmG7neyhUI4c4yQbCwrDFYYAgljUX8BmgyUfPpOANKIAVDEXF8XShYFIUu5WmpFksCBfiYRmi6e8nqVf5YAYrdrjgxmT+Q+ihpvjQ0ihimmZ3RJzwFYXb7vq5BN81xgQBJWbTbQ5SZic2joS/aMcWC1YFlQ54Lr6zS2w2rIxhDm+QOYkjjRMK/9u2ombc7rt7kJPrXVUrpGmSrQuCQlu1R6o6E1tdg4xatEC22IbarGZ2gN9SzLrjwbqgQLcXnf0Sbq1lisqHQz7TM2UZ0jMDMuhOnNTJHtBSill1Hm9uaYb0ZW7fKV9A8mnWeoSxZN9d9tZTdaPfGfro7hdwafLBikJ12dMCcWeOj5csVXXP0JTs134muy/RzLnaPzyG4tdshgrHnoPLEC+I5gcUsyAPUysTt8Kyz1Z5Dggws0qxvA0mlzYzlQlfFLSCCarhnJUEjEK3SRtuqDg4FY/jPKGh01rnvdUDLl/xBGnlaCTwACiz1099np4sxb2YbLdhXwvd+IS8nbYDeblYsj7eatXnFRWzW13V2qB0Pb4YEy+UB26L+pdnoJRVq852g/9gJdIJ/ZIYlrJuH7ZSH/ryI+61iEUw6Qxp5Prox21xLp9NblfWO7B1r5s4VfT1uM+dsVhn7EmNRDxoCFMrUGxGRdw20zOy3759O9AILDg2i7cDHgq2/uqB6mPSwKHLq2A5FoXFKSjswpNrWJvpviumhlZ7jaiM2wC8Mom+TEr0BcXeBYVFjb+BocNu/0aSyRYXpCPDUEJvgWPS8DKDNvpYcZrg429m8omXUMeg1D3/wcn+AKMXwGP8vv/t/ZXqm/48zPb98PocHBgKGAAL6Pc34zDIyCuhVdxHZ/ivNM6l2n4l2C9wM7VYd7RqE6TtbDXQr/7owbOAjy+4sN6CoWqL+zlZNmyI8H4PDweoq2vlVSogsjDv6/OEj5e5JzsCBxT0orYo5LRqQIgvPyOjfFNNohiHQ77rfSals9cJw4j1OzzVVg8AFddQ9m4Ql1vNLOM8EYCA8cIb+ODzaqXEJDdwG1f0inLFuThZcZEUvCg8q8Ztiy0+112GiYUUYOHGP/euafMF1Ji2+vkN8h7+tGJbLN3tsopZCXCFjjKfQ6KiARup1GhrNh1KpPPDrrcatsaegoEBEYouIcMyUYoWfAN0SPa2uqN0z6rr5kCa+zsoy70m9yMeNHDICMJ9v0C+u4IfAxvwnMUYl9BasWW9BM0Havn4bXTBLKVLKRz/74tAv7wnmyyTNY1+MFzj5lmr4T5cPDAC2/jjU0NAgIqUuU0si8Z9FPDT6g+jNopqqJoWUmI03TCo01IEhhckx/Gacnp62RT4Nbtc9fU5ny4KkElfcNaGIr2NFfJEz2RfBMOADbQq5Y9kP8RXVGmYveD9m5A2rqpWzgGbaySoYUpWppPjJNpMVM9nb2yL+vCH/mZZnRqb/ILAYGAT0bwQhMCgo+N9ZngVQGOT1QJGJmIgZbWOquxQUff9I8lwKNKE4XdJpP3tRUoXzlYd88EhPVMwcipFLTT5mvT/8WfDsXJ0rNCIkGpQYGAFPAystLc2Q9f6i3+9uBgv6ROEQUQpPMH+RKJE7QKpKhNoVaijMNz4WsmtR88yclBZcQZwYQs96qCypCVOCIBw3oIM0gFZUfpgExMB6MFsqJt4uBLC4ckau8NEQJ4eflfU+dAqDMxB7Prhrln69ThQuO/Crx4Ct6qgz6rdEMoEyRKnOaLUL4tBanjIxfCWJ4CFi/6XCVKo9KH51u6iOnnouJjSiQXbRyCgVswGhPrUDC6ZrgFH4G2qRyEC/RbQUAZ8qNKwUaF0NU3DgTjUzExpf0zwMaCC94tJgRLy2IZqrf0hLS4siagatCvpzWEcIW1KxgleoA/ctTKX2GbJv1OtP8vf+KOJJ0Q0X17ICsDbnXZr6MRDaNgGWd+KWCiB7A/o/gJinII0wiJBUsBGkLk4mqodSvLRtBl3vf1szKi9BFTFIesm8dZGM4FGy7DSdphNHBJ+gKbOsGDb9RuCs1HRF0o6VajUajAMb9VgcOC0i9IoESF1ylbvb4Kgx/86BJb68Z5SUd8XtdaPQb4tri2IsvT5ElBrLEy0/dGGrjOeI1N/5sRbpftQ/pfavfsAKhBOlQxrkwp/6WxEKO0aeOca+7K5cdmcfsdqAgrdgABw4BVY/Z9wtqokvWueGncxOOQLRIvaxxOpcDqgmiOcQV0oXdvApZpQZD8oTgPTgUQVyVSx41F1+t/CG7fVZlegWt6jBcpQI31DLEyDhu+0Znt48y0cAVAtP94f1mburwprSGvbQQ7yjPCL0AdbeVdHF2mBL5MHCQnXXPHU4tccdH4nuwEC/49ntvPfT7Zyj/VKdmAcTFsdBKq+UxDiXMDfq7R5GrNCU3NRAt0O4BOFukcn2JucPATRKZu8e+Zn+GtBXtmfd871MbBQpzSS+oqfM7O+qtCmzUSh9UEwAFQlyoaj8UMwAVckiEagsMCwA1Z+re/5rwc3Av++Zntlm4B9wM+VPuBn0D3TP8sgojHpgqEyCtv9ge74bD/3xwI5tJR/KbqaqCU/5HuY/e57xQ7XfHl0hXv/MhNZWrsru5JQdXCHfFJVyPvQ+muxKLL0Dj3ybnmzzIwzLeb43jJcOldeWnJlb7Lel9IyhmKh94VLBM8kVHPBdrjoXwULjhptFewddop6I4EbLV+A3vekoxdgNLzJwMamhRVtspCaw2/SYEkZAVUIxL8fJypcb+s9iSmmUYAwb94ucvClx3yCIDslfC6iyF7GIWnB9vwebP5TOe8tNqo23Vuksbk4VP3TPOunFEpUjojYrfhhw1xz5pB00mD1WkLpcH3biU+7rjGGbCH1O/FMGRttEJXI5+791taH/LM5kJJ/gDuLvxMBO+eNwlu2TwVojyfOARCPwvsy94WMicYOMudxGQpTTauy3IcsYi/kpzGp/SzN7QbkX4XevM8pcZS+TPdb+x63464Tcm2ed83QmUp039yG7BZbilkrU52fVs9aNJU7S5K1649UKy0Ti1FAEfH6qt2ftb4tlTcboRUlo03zgGM0ypp77TG0OAM6bOZ5c5i6M6BY7APtQUWJ4LYqC5N4Q6GfwHA3G5x6ykAQ5DSvE5HsXmhYtY2O2Vaf7RmBPZWXFYq7PpHPw24CmsWGpNHTKNwYiX9PaslZmUb25PfgCgjS9qtbeHXEXTppLz2jnkngSJ+WidoUkC4kNdc+4QYKfxIpqesIi1kd8VSFWXfjAz8YV1IE5L1Ge80MangAuLMXLeJkmMohoMSEh81cRjMKxkR+eAIGB88lYb0Je4nY9AWBhyxmZh5AkufwfscJMfQvYYwlX0x4DROo6Z3AkEI5lvAVzlnVNI0mCncn4soWlyHO1QDLyMgqCE+VFmyB4JHikEalzImzg3GLdUsyglaKowXdS/OaIR4CaC7Lqxc86rcx1CMtdAuu3sECn3q1hS3lFAJuMHEfkd4j6/tQ/S/ClCV2MuBfnZY4T3hq2z07LfkZ4YFzfN4sb57g19BwqkWX/vJdwRVrMvZ1ZoLqa4oQxbE1sZtUT+o+BQS/zQLBpFMLCf2XP/wK0BgYD+iF7Zv5OGIFAvvjVR/QdsoRARAcFRyJUiZ+aRmVgE1DSs4utRWbxq2GM6ZL/O7BSsv017VBJnBDMLUPDQWAwT8+Q+RHrjH23r4mjhiFj1WEmsc/AxTaC6BH2tinniMTBS7Mj3pnzAbYjtHKp/HntuI9yGI9pgpBruR6WZOqmPG8qwwpLvMjvsLskDGi9j0AaTVxRApk1wCe5nIJiON0Kt6Kq25Ax7Z8AJritQoNJUybY/EfLeMJ7+5mhvP1fXhlOPGQ5HcETGYhkWT4vi/yzMYZ3fJe+K3XcIRFovnVwa9kfZTKKr3MPrUH7tZ4AyxBWk2ekv6yEasN9mA9/9mXNZbXWV6FTBprc+pLPJfgBYWqfwZmbvoJBZr3TDPOZjhXA4OkJJWJuCtuOFufb3EJEN8DBm9xcD24W1qS8Wj+LGvgKdbzkrlbhln2dVGn5SyPKVFK5bI5+8BfZKEjdD4xLBliCW7ScoUSvs7Sp/YW1HXvUhdV7IaNeq5N828UwZpGaSs8T8ntvuYqjd/Wh31oICb1c5tJ4blStnvGAWu+R1qmDRxJRgBbXPh/GlrCFzQd2IV7YcCy+Oi9xd12AbVUencGMzuSRxqmSRjysGtGi9MfuUbUaHuk37wdt6bc3RM6XZhR5odFoLuOtVLa2Ia4qEfmpsXOHZWLrcEddyyNmf9AaXME45/sgrF7tG9FkfkJyFS8SS7Qxt4fppKiUYqI7HbGg5eBzjGe+TMM6Wtvd8e3QpzNGHuYSpw1cPLtPqXJNOMN8D8DcDQuXAl0+g+XMlcS3MNWEh9rjz8TLYjtURGTt00KUoZ46wMp2Z7q7FFNjTTxkOp3Dc0Z3ufMvXVnTnxfyz95TXDWG6s57H941JrnOgB2BGK+19Yyngyh+KVxfp/BXfwLUHq/rfX6FXgf7fdmfjRXAGj9OtLoGpdPrTLJ6roxy702y8EF5Hm0lsWTe8R7t4Dn8so7KP1f2/BcCdf4lmM39Hcz+loV8AQb0OzCbEByJYRpdQOU7lq1n+x3MZmQTVdKPeaayY7uy/xmUfVzdULUGUeSWYGRs5LR4+KivbOrQMlJ1zQ7jJUMIarXWZkmmMO0SW3LOx3Q5YHz+o+sI6uI3OLOFJHY6+tazJMb1/oCyb5L8rWo0NsBiMceSIE5BWuu4wwhnRHWdfNeW8UQ4ksJt8LwYem+TNkDbGXcgTLS/dQVi0pi+yxDOJq5IHYgRxGN9Tfia2B8ik+1B6miPJ8+IC8I7j56bCYX5StmAc7MY1lgUCA8axFEL8CJwdvpBbZvgfmvnlSeH/P3QE0D0mmQvk56L//hbP8RpMgo3yfWtp0ovETSufNU1r+m9SMwRcG7WfCJ0pha+e7dc4T55n0ihYoSHC5Yy1UnNBuanxd7G5iYhzP8V2vslpJDU4HqoPDmu6MagIHLGm1Mz2gVbMEilpqRXyGiOtnh9XZPZ2vpYvKl9rWVWUffQ7mkd7soTFnwUYe7p+N8it2cBM3MLcWsvwgceVjY1ZT8ta1fBoW3srV61XYXF/GoB5zj7z/FWz6eSonsiocdoiQOVSFLlu80twqGo8jlTrZVyMYOKDIzgC7av+OZarRdpduygd9ZsvIq8pNDuOPrOrb7vSaw3e3/PpdaRp5vOCMagtWGQhbNWW9ArYvtgo6NO8AWKzSCZYLlubI6Iipetjd9OH7M2J/W0hXaSMXhHtAtLpZYYry09kWUih1EV+LX64colowiqa0zCUOcMdzhXJ0xn0Z4AQNb24Z6WKhP7zx7r83hPywX4/aCP1Vw4o3192bWBLbZgRvSjFuUzUdlvCHVdZkJVMSHXYknFeQieAN2FbDCWpVb5rCBW6EKvfKwGkInxYr0/SB4yNETUqPJbdg96VG8Sza6eLoRQopGy9q65FNXS05uVvImZHtQ5fqk0SCshp0OrPKYRF9k7u5OIwZZ0oHYCNMtjvlxLRX35vj3pW3fHGrn3xT7pPs3PZaXdZBkuoPMUzF3HyDByUfUcqVSpQH6NF84eP+7dSP/ageikAy1EMCVGjjKG1SoHxDTeBmpqGDnrd9PzMzo9ykTm9N307EX6N9Pz8s51KWTNgHUS9T7cVSMiOuM7PKWjO5EIQKYVEe0bLjB1m6ruwCeAvYfCUKKmx6nRpLNnUnBzbAel00N3t4/YDaI9+XHOnM7R580h3sbGPtWReC5XwubspsyQsGShuG8r3Nnx2/q2wjdQuFJnAw8rW7l8pJcXX7K4vnWxyU6vjm42a49P/kkX+b8GbrOx/4eonlm+D6vAQCEgwH4zrPoObhNCPJOMqOjKcdXTjAKKtrHZU0S+NbXdXf+oeZ5BrREVe4lFISDQ9Y/A9m6SqQpzunjFmaoX90BSyuf+xgi/k7ZRVrUwRqYfwLaUeVvCxDzrRKhXdBGXcF/64Qk4n+TYZXr43ad1UK94x4jarcw84rpX6uvjXwwucusOjTdovxBf5JZZZqI8EOLm6I9fOvvj5+MWGvDeOPt+Cwwsrgv3II+Q0Zxr2zAeyI+4MK9G2iAfKLsP6sZMGC8qxyQVBcasGwxD6Nwfzcca88uWQWnCB1RY6irMjkF8dKJq/ojX9oxmBxuwtrQ=
*/