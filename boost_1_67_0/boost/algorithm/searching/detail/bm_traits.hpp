/* 
   Copyright (c) Marshall Clow 2010-2012.

   Distributed under the Boost Software License, Version 1.0. (See accompanying
   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    For more information, see http://www.boost.org
*/

#ifndef BOOST_ALGORITHM_SEARCH_DETAIL_BM_TRAITS_HPP
#define BOOST_ALGORITHM_SEARCH_DETAIL_BM_TRAITS_HPP

#include <climits>      // for CHAR_BIT
#include <vector>
#include <iterator>     // for std::iterator_traits

#include <boost/type_traits/make_unsigned.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/remove_pointer.hpp>
#include <boost/type_traits/remove_const.hpp>

#include <boost/array.hpp>
#ifdef BOOST_NO_CXX11_HDR_UNORDERED_MAP
#include <boost/unordered_map.hpp>
#else
#include <unordered_map>
#endif

#include <boost/algorithm/searching/detail/debugging.hpp>

namespace boost { namespace algorithm { namespace detail {

//
//  Default implementations of the skip tables for B-M and B-M-H
//
    template<typename key_type, typename value_type, bool /*useArray*/> class skip_table;

//  General case for data searching other than bytes; use a map
    template<typename key_type, typename value_type>
    class skip_table<key_type, value_type, false> {
    private:
#ifdef BOOST_NO_CXX11_HDR_UNORDERED_MAP
        typedef boost::unordered_map<key_type, value_type> skip_map;
#else
        typedef std::unordered_map<key_type, value_type> skip_map;
#endif
        const value_type k_default_value;
        skip_map skip_;
        
    public:
        skip_table ( std::size_t patSize, value_type default_value ) 
            : k_default_value ( default_value ), skip_ ( patSize ) {}
        
        void insert ( key_type key, value_type val ) {
            skip_ [ key ] = val;    // Would skip_.insert (val) be better here?
            }

        value_type operator [] ( key_type key ) const {
            typename skip_map::const_iterator it = skip_.find ( key );
            return it == skip_.end () ? k_default_value : it->second;
            }
            
        void PrintSkipTable () const {
            std::cout << "BM(H) Skip Table <unordered_map>:" << std::endl;
            for ( typename skip_map::const_iterator it = skip_.begin (); it != skip_.end (); ++it )
                if ( it->second != k_default_value )
                    std::cout << "  " << it->first << ": " << it->second << std::endl;
            std::cout << std::endl;
            }
        };
        
    
//  Special case small numeric values; use an array
    template<typename key_type, typename value_type>
    class skip_table<key_type, value_type, true> {
    private:
        typedef typename boost::make_unsigned<key_type>::type unsigned_key_type;
        typedef boost::array<value_type, 1U << (CHAR_BIT * sizeof(key_type))> skip_map;
        skip_map skip_;
        const value_type k_default_value;
    public:
        skip_table ( std::size_t /*patSize*/, value_type default_value ) : k_default_value ( default_value ) {
            std::fill_n ( skip_.begin(), skip_.size(), default_value );
            }
        
        void insert ( key_type key, value_type val ) {
            skip_ [ static_cast<unsigned_key_type> ( key ) ] = val;
            }

        value_type operator [] ( key_type key ) const {
            return skip_ [ static_cast<unsigned_key_type> ( key ) ];
            }

        void PrintSkipTable () const {
            std::cout << "BM(H) Skip Table <boost:array>:" << std::endl;
            for ( typename skip_map::const_iterator it = skip_.begin (); it != skip_.end (); ++it )
                if ( *it != k_default_value )
                    std::cout << "  " << std::distance (skip_.begin (), it) << ": " << *it << std::endl;
            std::cout << std::endl;
            }
        };

    template<typename Iterator>
    struct BM_traits {
        typedef typename std::iterator_traits<Iterator>::difference_type value_type;
        typedef typename std::iterator_traits<Iterator>::value_type key_type;
        typedef boost::algorithm::detail::skip_table<key_type, value_type, 
                boost::is_integral<key_type>::value && (sizeof(key_type)==1)> skip_table_t;
        };

}}} // namespaces

#endif  //  BOOST_ALGORITHM_SEARCH_DETAIL_BM_TRAITS_HPP

/* bm_traits.hpp
znEIRzcNow1K7bS+UogXAYIUnctokto2yLZljBfcidZAQKC4AOsCVP/N6Eg9SXN00av6d+L1PoxgJ1Mu7dvFptFdvP5jgw2IH1ZIyiqeo+W83ZvooXfRahl9qx8lbSHgPninRy26eDXDc86HsDLRy57h/dx94YszPMXwgqcNQessTG7Hflyi3vh9cO3Y+Ke1ZLU9d1WVnPOU9CIxu/2QwgQGZvLbGR9M2fqTVr4PQdYACVq880xZ99fhogA8kdmVlLdQfNUICJ9BJ7gDHfnIrM/YZvVCE+Pl8XgYeOPXTU74DIai2JzVKZeMVJU0o3kfXzS6+kcWN0UukiG8b2hPrvOliW58rbzifHLoDldUTIjTxr8P4dilrplGis53ESG9LLm84Nzn0AoY3t/raCkSl8hqiSHIuyUMb+jG7uPsXOXYoOYxvN2wjPsA9PyUPDsO+tXZ92EBaoiBM3XJxtE5dLPWL/3ytcB7qnPa/mUf3rscDPKQg/NVbNjUVXM7YgiaEp2aNSdiiZyIUKQTpDDiYpG/BXnByPT/jrxg52QFsrKycrKyM7OwANk4OTkERUU4ODg4WTg5hQRFGfmIeJ4UAizsbExsLExAYSZ2FmYRQQEWgW8XIAcroyirwP8la4ANAASaHgAC9xUA8mwcAIL+GQCC861OqAYAIasGgFBWAEBoYQEg9HQAEIZGAAij6b+3BjBzMv8vefHfJi+YWP8TeaHKHY3PDs/T0dLVi0gGSgbCqLouF4VUGeTT4EhtE2d9TAHz7NxRpaQ47ZBY4Im9OO47Fqtp8CH8evl4evO4LeZyd4qkE2cdp3EIwfA+jq3X/RYwqC3ZwCVvqTCDmlB8FzSIZXiYZdU8K2/N5tRuwC7P+orT/zBOpCxmp3Yy6b5bx/K4XEmDVLsFTrOnPchsXMBONkvnWrFkZEwGfsb/yuMKAp3ec7SKKq7/gct46IPDSa1jhqZZSEoBu8r61m4Da966J6UQ29yYDAWUueW+0cCXHS19p+n8u+6shaaEzbIv87qtQRbWKept+nZOs8DbgjgfxStFjdjxxasT1/qrRpeVCcklnjYQ7ryl+/rxh4PXJkrrD7Evw1fEmmz44O3dg0exyvaarUVPfbTX00xoSOnzfc4OSmbO4osGLyimUzxfOaTDG4qSxSRxDrhszC2ljVMvLYTLiFY9q8PfDHXStXOiIVXN95lY521fJfR6OL1xwwBJFvm0TQOGKT8fP0YHRkNKZkpcrCfQKIlkezj0ES+2xFl3kiTW1ilyUsBq8yMqLZyYbUFPt87gB4HzeFOmtqa7h8cbB+h1WgEHYf/IEQMMAWVBu/DRgvLFXBUCmY8drtSU+yiGhe6asiGFIhvFHMZQ9dA+KjryPNhmHylDgrTHZFiskzAmU1pWVX3MUN4VE7e8GSZLtyoTBTpGgWj0JG3lpyOSAa8Invver+fZNYqLk3shod+lq/iwvP5wghrQ16gyvQdLA13UgIkbQOTQgNu9K+FSqeqDuOCn7dWXLWfjc2aBvEXV5yLVA8qA34d7uB4s0+7AgnBJIaS2SUkRw7a/4ZqSiksXk6EtdpmCdLA8sJo8aKQbuSS0P2dGptDPvF6KZnYkrYGGvGBdYUyrf4ywvqSQ5/w8n53r5cFWg8A9N0MMsW/k9QhmTAqI8MrivN850+RXRfsXGmQE2c5dOtFMH4vgt/fUXkJszquWbdJnSZ5pElgrtO1eK28PyBkJA5OSYlLFwstEbbMVK53EKHOgca+B69/piyYgeizG8Ze0sNw2luhI2SKp7hp48cmdg/BOAZGN+v75bref9AVXk4n5c9xgtGqdkqFstGSrhwZXM5sJtJcuHEnagUSSFE/0RVkJJqhecGQk95AujcXEznMoq7be13JSaMz7eqjeKAxCucYqRgn6tMblHGpi1iGcVPKbut5hLbL8AQ3cXbPBS8xoNArI4w7LK2UDVuplLzItp3N6q9Nj1YiqWVcu9Az4gpiQKhoLjUYCMDo0F2hpRSNNtbloNKPyVkhMKFA/g1xGwG1J9nQr6ag4shCiDRkiY68khOS/e6wdJVCGugtcbJqonscSCqNPE6IQpZUiss73U77i1ucusUy75hT5COEhgzZPVXfojmZlzl+sZN7jGzI9RAg5e+hD71XaMHpWjXKIprg06NqPE+16R4PC/Jp5bKuS4Au8dym0cuhzw+Ugo9Wo9+Aiw0MGzt7VQJWW8rr5dTDFbZMtA4FMu+YX+FqeWxKvcmwez0nIJag7Cm+oAlqDS2XQpsrWGcNQHue4vuKIFF8nuaCKQFw0E9HD0imJPT5k02855zZG2D3TrIUbtjtg/TC+DYfj5OG522Hn94JjAQ1oib62Oz9Vv7izPYTadNjVz0gI/cxjxUnkeWih6o628cncjl2W/nsV89XprJyzO1WYLXXjkal94bS94PpQOZHJBCyOSF++Lw17IwjoJ2gHYfRZ4fPSr1RJevTRaJ7dG2HinHsLKMm6ZY8n21WOb1cXrTzDyehdHFjEjO4pkOSUZqncRLKZWq2pruPDq/lEXmVFNl8LClHA9Kh65o3YF+XlQuyxAaH5aHIwEOcf7Ra7UyVbmrOeXvHeN/trn0m2OZfb+JC2Ovfu6XIBAe0w9Sm5d8Wk7A6e+hR3xPDYpPYDkv873tUqzNrkI+gXYlEBO3R8L5Ts13d4OF8k3vZH0yrim576zBM8q+cCFWm+o4r6/vYusT7UyGmZ+fR1rO/rzkPW8v+CFP8TkALI8fcFKQBg/7JI1fczOtQ/z+iAQv7K3vm5FDsqk8DTWZ2nNY5JmFlO/+S0zvqvXHeKX7wE0pGhZZ64cEdVBOBx65+NgkuDFhh7LIBNT+B3hkI+E4r2NLIBmALRHAbgfBVq6Qa/RksAZmtgPmcMo3aCG4Or08Uh2fd2KYmkTxTOzLsBJKHe4z2KSHgoxjSYFRiDxZ07WQg+Fn0x5BKkzvzVjbRRjbqUcnqCMod+Lsy/BnFi+XtpIDorAqg0EdLTXKBtrT4UygQpxfYQbi7gkvy3vW4WTXds/MCIx6r0xeeeIxHDOV8Bpcb1Qxk1Bud0D6R7hBXljCyr9TwPhhm5HkKXl72QKVd9GaU1FxGFnu8bP0x6zp1fRhYTTizkcL3ePfsKqEYXutVUMn6ZxvfqSrDQS8osdDemYOhxNHjRdbrtA3N2/Uqd9Rv4nbKGMs0lMHp6emDN3e6XjKnBseOCLS9FWv73GUkPLy1p6GqB8QiZHz6n2zDVFlZ/HFRj8wULd+nuncgeEqLWXYBH5NxG4ZqpOKnNvsOF8mr4L+OOUoL4Xkc6rcgkrOMP62qsvhNzoz0h0aik+Dd4UpCVrprYc1W2gq8N2sGCJkKyae7gZWK1kVXn9O2zd4Lfd6G8Hkha1OQmJYUw5BM1+kVXRCX9ois2jJRNKYumde/eIkJyS5aRXXKVEr4B+dBnqpybXqDsewTgwDrE0WqlL+7q3R/71JvAAGdWedp8fsOUN9S5UMpj1foIH1d4RNC3HGDFCDUhOeWEZHDU1YAFtktuxh1Qda23GApykTxiVIX884L6V4IVnMz//wErnjzy/1jMHAwUDBIC4vdgBRPqd67iSbag7x1VBWRRUDz9M7Ji+u2q4kSdLvvURZkawr8hK56oChOTj4dZpTPmLL0+97thEF8mceDOi/pvIkv0N3aQtgpI1wXLQmIy+ZNTI4Jg65/LvH00JxHM644/eWvF+2eR6YoKZjXRlzqWY1q4+WfuC8lOcX4HgXyW0iDzanRv4XawLF84qsARgd5C4srhx/n0A957+09r9xUWH/GKqNrs0aL4jAPLN579saSxucFiAKfQ6kDnuIfH9EF9rhuc6gkJ1wGTwChi+BVgy1Av5VVV92cR29ppSkh4F159A5dl12d2THx/Tksr+8WAXqvn3PC2C0s7ygjgbz1DUnnbF9CFBIgIs7eRrK/85D6KQ+00dS0+lJC+Dl5+wfraIkqzELI0LJrWATBjYFGNNzX3+2LCi4vB7ib30V5n+1TifqdtbL2AGGQDPs+7W83DzPYZwYtBNTyRgJl/Npra4LsD0XT8BdoXJbXEXsH7YWZFWl9NJCDPdhGL7LzGfajNx+4zdjQiq6pe0vyoCP+5poUZRW3ein6H2t9mfjkpiM6iAeMCXYyHY1r0lqqYc623mH1cRH4MkVX+fTCNbYNT4kv3+pP2AiHFuJbWToPNBr8HLpzUJ96CkL6VYffjtLZUnKEu9JSWTvGeVgktQDR7/VJVYVNdDZQVEzOXhJKPGCESMKcRGZh6847tBZiemSCJ3fqzeQCCX2GvfGaU+JcEDaZYEzIFPsOZUEMcGLSIJIf8qtRqxwH/BTVYc+whSotEy7y3/2wKZnc+xI6g4UX7CqDYvyjMcQofTzzLGZc9s2qX/H3fT9QCshka/JlIxxLOk70BE+qNeYofu9EZH9mrmd4ejzC7N/kHK2LdIbdzcxVV5VZoyyn9N1FemrjoV38KWvyj6RdfMb66xiVKFnmh9E8I4ztkwfEdsjj6CVn4PkEWK9txv+tSlSwUgc2EwAHQ5imR+MmBhgHQJ4qRBQtBRN/C/qXExX9Y4ecvzgp8cjWA/iAuGH+sDwcGCf4HWwMqMQSTANoTb5HFLOhdRUJKBtT/4/LD/0AucKNbqJqymmirQ5K/h3lzMqtMBEotMItbpIMJetzu3S5Kymme+u57NKPtTHwO6AAULOvTxq8SM7i4UBwNq3KyKI00cb6H2RtP17Ka4nPWegcdo/rRkuGPht0kkUGx/X26rs7J8I3vFJCBSVgHSLKoAgnPggUpFEnxvXfXzWmDlIEwkqFvcSvCDG1o8gWo5SPBHE5Ly5/oCxogwOo9q2t551dAAtaR5YhOSWX7Zi93ip1q8QHDF5vwraUp1He61X6Yc8Cz9ks5GWSfQbRXukODXwHTAhyicFTyHr4MtF8BSg723GBiqkKVLE+B1lcAch+++nfMYve/rkiKddvPUSS+XBZAy3UXk/YxfTcyhfzPRvSAdcJiTMsa+geEtn2kbn6l54tGmre4bjOEgZ6F2vXDDRds12Xsz0JHF4brK4dS4ppnUgJFjS2NNNUMRwaXzaW7SZnra+hLgVubVnVSESMBcUJ4CZw87Qt5fVtdg1nhUqnprw4VPp/rbcr1kY/KMlyldtjQS2S1eN65TSY+Jy9iYbdetXa1g+iuo/A/vDs8lrKhI73a1hsoNbUif+e59ERf0HdXRiymBVBU5RLC3o67ZNQR3ajOhAw/FEF1vq/VMT4UioEX6sdWr4hV8zCx1Qt0AaNlPQtBKkN8yYREZGj0Xl7vsng8yQveT7Wxn/PWUjkH+IgNW2ETaXexUCJqeA9E1/lMtL1bp9Y1zHg0LEFnkYCxXVmC5eKPPx9EHha9vnSFboDE2NXC9G3i1dJM72xDxPfRC3lnr+glecHhCOP/HHlc+oH249ocBVajmAj7RXm8O1AShNTmp+Jh/afioYeSAgKrhBbCkFdkl5ORqkddjZZ6j0FiwFuUZvDb0Zi86+DJzaiHisooYE4zztDZ3ZivhNYYYEE/WN3Kx5yhHFfzlg1jU7EKeEAuyJ98fF00l+SIkkU44nQ3dfCyBUYuYqvlYW8WkOTb/2XOduGDB81/EVP3MxbhzyGMcH4XPTQVfBc9sLOWCWlMfXt4kQy8yzG0NvhjKcFvIXQy5FyUm1FPfGPYqjQhu/jsHrhCYxZTz3lj6C5RLDO3vRZ3SlHEbZDhr9qd7Ig1aE1qZLU2mOYPTOmfT2m0fYIxztiMjvCKwoRemuEYyM3+peQFK/vfn7yAAv/WyfOUBAgKAQPxj6nxe770d/AC/Dt3ER07wa5kWzNOwiogb+Ojp19VDWRm8Y7q+AM0fynRuvp8ID8qsyPCCNesUB3qEz9ERe6C9BgMBPGIYfRAV7V7OEhAjj+RkEPy2o98aLNdvpjzPvZdDEvauFHtmA05eF48YlDc0lmE3EN6Shfa9dlJvgtn3J3cigT+U7AmE15YwVtqsGfc8b4fk2+NVyLAPFC+2H0FfG9IGBfH8l6qJXj3c5uEoYyb7/X3wS+6ETczLyjeJ13nfFgVfv9t7vreQH6hAEnkRA+VxXox1kYAeUt+tv34vc6QHcn0tDcYvusV+avHj7FDC93nPVCD+opi5opjaITkIUrXU0Ka8i7cUHdywTC6wvQME8oHU+bQQVqK9fmVnpZ5yGBLsyDPQHQ+rDUhO5LQ+9uA7tarjLe+hYJWtf8+GNygflt++ExBOhWfFEZRepevvUD8eyI/6MwEzK8AOdplTS/BwOp9HGNTsyW6haXAynEz8Bf8PjUGj7fZz7dwX5q/10UTqclwO6a68zL5OSTUb4fM+woY8bvkz34nJ/VOEGwdiiXSIjjgWlhtgvf9sOD4GQPuV0AnSb9dN1RTd/RnRUflC2HtEQwNqH6lwHq7Y49NQutD2KMkN7V058wvL1Vrxxemvo0/oD/N69eTVw6ovRcxQxagg369OPFsXxnBJ1e4Bs0CyZQwqUUeQxN+AdGtjMNqXg46JJlkdWQT21GRJQwHHk5uWVn0IyHITYVJ7gJwDOaBeMTIdoC7OjScMyAnkLTLsjjrRzaymyHluL/zNgTJSH50E3N1aPC3/uDf9Ltr+Bsvy+J6KMWNGD8SOjFDlYlrtRHpXdsxuk7KDd8VfbYu1prxWnuqT2zugiG1JPnOJP/YRGGr5ivge0MCgziWx9IwQe0UM9+e8+JeAmvGzfd6k+uLrqMt3cv8rKRrxd5VpabSr4DvDXlDE5Df9+b1l2IY7H+vA65/yS0GA4eA/K0AAgIa4lcK3J9jGE8QBiklkF1QVP6Jw2Dxrlr7EwHEpWuZKm5A0Qia4l5VfeU0VKYjzfDo8CHT+H138cR30uLN70kL5S1P493wiC16jQSp0hYkn7d9A91EYQsNYd8nFupEGgctgQsmyGWyuvdSZMwpjEgrT3wFhtA/eAi7nwKIAwP36POhRHy9JzoD78IISg1/LeuT5C8BhNoqmd2/9MoZFylXbk90a7eBM7qQPYEYx78HMQxuNsXOKa/YByh5vvwgO5DHRHUdngQQ4Ic/BBDRi4/e2MMMKcpjZoQ+3cZiM9N2CwGfqsTJK+uqhCGr5qAe4vzVyLIVJk6fV2SDtLjJvdMxhpsPJfStjyUmDeKn5BYtqYdCWF2DVsZKfImKYW+NP+RbmaVlQMpQYlDnGWUCduXXNvqqrPjYnR8ixC2NUPP7jnqGjWPc1Pv9ze19MNB1ExgeTV451ljf4noNaqLVU2sPJC0PmR3hJC+WTYQphKCxZt24vLjF5EpbvY0iCZK/yPGXicZ8LpgWFMnWEqx3p1H/ALqyTfTechaqDKlDf9WY41vIW+gJhyLuqUFw/hDPFLmyiIFftcxKmkwWy5n3YS8EIcWx4B1+UAeSvoyG6C0Qg/0EiPAVkN+NBb3yTF8bqlUvfZsjel3oOX277lySOxtMg5ghRu4nTo6AeVgeX6V5FpHgo+pzfCvj2kOI9jn6I5uItOL5y6ybl5r3m4TcDl37Qidqqa+70Gb42P3bWjow1UOZcanArXE7+wU/nNa4HojKtFMJ1X2A7Bx0Y2zAVcrvqAJILvuIRu2zm+H7EXm9K387b0MW9tY2ul37806ImteLLH0DC8Gj1Y9o6olYz5W1ornU4ZZbi5MgBmjgegabShRs5pJTJ7oga/DN8XW5oMyuSgeHeBkqjPBVCqRzmt3xtvhkBHgsZ2otofTecHfozCYlGeSjf3tJT1PHOsn6pvYNDA31LpuLfnTEBGtFh5enCWW3wvO9CWgYMVofRODRA5dLRWrt6a6BH1jmM23MbCR0CQkS/2mBOLZzn36nblAwjOEApdmOjImSQKC0eycSBki/F9YSd4StXtPz+/avVXSfGIjXcD81+ujgVoVsQ+757Yf8/AAR18g2VEfZ0zqHxmsDvBXWyRUJVPZnQnZCNnznmCgBFDK75yMjEN13w1riaFwJmxHH1smh9ymTk81vn+gLw3nmgm3HiJburt72v5bEYP57fTz9/THYt9kTEhT8O4nB+53EAAODgvm9BAIFApIY9YnEEFDWs4lBJyFV1I+u6pjAAEZlVdd0opEpeP/RSPw7EIND+F9AjOrvIAZJy0DYv4AYbN9BjCJppxicR/nUy4JlZJBRCot9Q2f6BybNbW7Oy8FWyMdEnhzOfdlmom1UNofqVozHRM7RUQ/bCpD2fCSqUdfJo0DO7pE0iwqI9nxEu5oMrZIP1ru+g8zptXfZiDbMxpq0Hd/qqQfbszQnuLf6Qt9JjDrtqTwW/CrPjSGg/s3dXLKNRA0jtpRhcxZ1nlX5Jw7onfuYrVRzpvbgAsw0ZuJ3tZolptJ1ze32iKAs2+Pq20hOndRamXWOLt0R5l71iZln8dNLmesBde2LL005JMUlqVRyMvmxSoqa5WBRXElyNfLfmulBoMUFWGK8NUuf0wQ+b05+41dN0gBSAE3vIlgrCAVhpjtPt/8i/cYNneAt91rIRGYCCoQ9rMzefdZBPxGV9ZIwLgkC9FeAPnnlu3GZa6RU+yNxZIObdjONm2KuMZInFONQih+9L51o3GbWxylK4Eb4ubtuBYc+y4rFA0wgorwa7RhWEu5IRn3ilCUuax4uYHmZyLeZ1lR/AnKYopWkPMn1GV2eAUTDw8fy/ZhXHybP3+XzPj+k4XsT2p67nCc2ClS0PJyub3hTfTi1668m83EFylAXuNv6rdAjj2xyenEXx+bkdQCqU1YIkl//gXzPT850HKVRp0ihfYCaabyJWqRc3zj423M85YInUqG/HYz9KB+zUzLIhJua3MI6hmOfcwEdOCatnXoK1p1zQcGaaj1Zs+KJ/EqRIArH5kbE8qXLzmSoS3NsAD6shBwbLCJXL+1rCDq0GA0EUnQgaJzSU4CbKpu8K+iMCfnt8ElckxUB0+STErHFFItyjt94JBzKKLVwYWFkcLD1R1N4lsyJoKmYrV1xvZhqea6YFvHIaGuj6KiPgJCvAIqyg6Vuseq5B/kJTmproyMq3vj2WFeOeVoy6C6gLlbqFj8rEwPZ5zC6/GlQKvePHH3pZkPOtVeGqUnxkTYzKopmHWgs4ngGPQNOGHK5KUrRTsHdgmflLNnRSVAgeCaeNrClaREo0F3a4DYNj50vs0fuNGhOQDLzd4Q=
*/