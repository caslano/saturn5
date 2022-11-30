/*=============================================================================
    Copyright (c) 1998-2003 Joel de Guzman
    Copyright (c) 2001 Daniel Nuffer
    Copyright (c) 2002 Hartmut Kaiser
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(BOOST_SPIRIT_EXCLUSIVE_OR_HPP)
#define BOOST_SPIRIT_EXCLUSIVE_OR_HPP

#include <boost/spirit/home/classic/namespace.hpp>
#include <boost/spirit/home/classic/core/parser.hpp>
#include <boost/spirit/home/classic/core/primitives/primitives.hpp>
#include <boost/spirit/home/classic/core/composite/composite.hpp>
#include <boost/spirit/home/classic/meta/as_parser.hpp>

namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

    ///////////////////////////////////////////////////////////////////////////
    //
    //  exclusive_or class
    //
    //      Handles expressions of the form:
    //
    //          a ^ b
    //
    //      where a and b are parsers. The expression returns a composite
    //      parser that matches a or b but not both. One (not both) of the
    //      operands may be a literal char, wchar_t or a primitive string
    //      char const*, wchar_t const*.
    //
    ///////////////////////////////////////////////////////////////////////////
    struct exclusive_or_parser_gen;

    template <typename A, typename B>
    struct exclusive_or
    :   public binary<A, B, parser<exclusive_or<A, B> > >
    {
        typedef exclusive_or<A, B>              self_t;
        typedef binary_parser_category          parser_category_t;
        typedef exclusive_or_parser_gen         parser_generator_t;
        typedef binary<A, B, parser<self_t> >   base_t;

        exclusive_or(A const& a, B const& b)
        : base_t(a, b) {}

        template <typename ScannerT>
        typename parser_result<self_t, ScannerT>::type
        parse(ScannerT const& scan) const
        {
            typedef typename parser_result<self_t, ScannerT>::type result_t;
            typedef typename ScannerT::iterator_t iterator_t;

            iterator_t save = scan.first;
            result_t l = this->left().parse(scan);
            std::swap(save, scan.first);
            result_t r = this->right().parse(scan);

            if (l ? !bool(r) : bool(r))
            {
                if (l)
                    scan.first = save;
                return l ? l : r;
            }

            return scan.no_match();
        }
    };

    struct exclusive_or_parser_gen
    {
        template <typename A, typename B>
        struct result
        {
            typedef
                exclusive_or<
                    typename as_parser<A>::type
                  , typename as_parser<B>::type
                >
            type;
        };

        template <typename A, typename B>
        static exclusive_or<
            typename as_parser<A>::type
          , typename as_parser<B>::type
        >
        generate(A const& a, B const& b)
        {
            return exclusive_or<BOOST_DEDUCED_TYPENAME as_parser<A>::type,
                BOOST_DEDUCED_TYPENAME as_parser<B>::type>
                    (as_parser<A>::convert(a), as_parser<B>::convert(b));
        }
    };

    template <typename A, typename B>
    exclusive_or<A, B>
    operator^(parser<A> const& a, parser<B> const& b);

    template <typename A>
    exclusive_or<A, chlit<char> >
    operator^(parser<A> const& a, char b);

    template <typename B>
    exclusive_or<chlit<char>, B>
    operator^(char a, parser<B> const& b);

    template <typename A>
    exclusive_or<A, strlit<char const*> >
    operator^(parser<A> const& a, char const* b);

    template <typename B>
    exclusive_or<strlit<char const*>, B>
    operator^(char const* a, parser<B> const& b);

    template <typename A>
    exclusive_or<A, chlit<wchar_t> >
    operator^(parser<A> const& a, wchar_t b);

    template <typename B>
    exclusive_or<chlit<wchar_t>, B>
    operator^(wchar_t a, parser<B> const& b);

    template <typename A>
    exclusive_or<A, strlit<wchar_t const*> >
    operator^(parser<A> const& a, wchar_t const* b);

    template <typename B>
    exclusive_or<strlit<wchar_t const*>, B>
    operator^(wchar_t const* a, parser<B> const& b);

BOOST_SPIRIT_CLASSIC_NAMESPACE_END

}} // namespace BOOST_SPIRIT_CLASSIC_NS

#endif

#include <boost/spirit/home/classic/core/composite/impl/exclusive_or.ipp>

/* exclusive_or.hpp
CMg75WdvRpesav65DjZhnYBEYyaPl8Kll4oJ5IMd+lr50B958hpAhaD93oEpfOz/x9rfADZVXvHjeNKkbYBAgrRYpGJVULTo0IKSBbQIKVVMTSltYNrC5su66CZqgqikUtMW7i5B5nTDyRAnOraxiVOhTITyMloEARWhSNW61e3p0rlCaylQub/zOc+9SYpu/+/39/srN733uc99Xs9znnPOc14+1dUIxCxxSqpir4B1SmPaumdpKlZ8pmmRV6FObYq8ijgzUPEc+Rkk4tWQNOyq3sG2LGZt/uzE7aLE7WKjoiFGRbLkRE3isc9k+FAorraf0sTWT+MCd6kfce+lvezR1jqoIXZBQP8MR45Q7+LTNvbvdgTV/PYT6DFgZ2gWBbdIgSH8Kjb7ok9zbVf8gzBAqCV21TcO2TZX99+hGij7emcI0cQ+jNnFRUu64IZt8RkjGE2zGEwViMForlH92KTqG6d+S/W//SK5+vyk6if9j+qhR59U73NUsnjuE+hQ1DxpqM/ipCP2HS72O0ky5M+XxBfTjQg2xP/zsgLljoObil3iJlmK3NlZZVJ+vG4JE03cdLVZfNDGiioXqUuRUCLTNV82o0Hx4OWGpyco2yef5Butk51Obt00o3W8CSYZuFOnDXtOsbYqoVHz3wo68+Q3Cxp7fkH+REESsvKv6dUMcKoo1+bbEmMg/VmodXgps2i+QnaaFLzYtQaR5kIDAlaC2ai9WzeNRbdjY/p/cjttmReAv7gvng2W2PKuJn6Hw8rAjSUsRjgg9tvh/Fu3G8YhUpq0qaCxz+S4ISMoQ7zd2vy7KnYBxcFaIK7VkjyNn1R1GY5SxkZLbfp8mmeVxQPjYXeT0nR43PZps+zJRjlS9cVurOp+KjCEgPmV/BZfJh3Ch2y0SIXrEgKMtEAK3Rv91wtnVTaIQKBFkCqmXG8MnJjzNwY1r/54Kz3CV/gImZ1yOyKPjacpED2jmCwZ3X/YZ1PSJVDk/s/AbiCWhwb0arEhdFM5oFdOg29+XB2OmirP8FeO6sU2xzrE9vqdt9OC9h8D2iIiUjylndH4aNBVB+fr8C4MzVvFLEVksUu1UHb1Hq4+lEUfJGvllomXB0iza5R0K5UkjlDBca0ZHa79NEE3QWYD6L4pCbqzw1IdSDeQQyW1MLNIL8Fyk4+hCwjW/xonm0XgCT5Gjf1HdhDqC+K7Q9HBhJmXAeYGLGm+/AQo61oMOPXcfQyusUMX6RZrsj57EgQuqNB3gva5NFPG0epFzSmmSiYvosFvnq4+dlrTxMHm5NPVg6cTp6sKf6KbtU+oPw30uveo3ETAjEpuKmUxH1GC+NGVN6UIGW3UjTo+w+YN1e3HJWJl53INwQfkMV4ns1hEYHWw/I1FWVKfMRK2m4Np9Jsa8kFzu/rrM5oUOraxjBYbrxY6bMz5IcpTBm4kL82Y6t3QEBHf+/oME09tR+XJ0W307Ap3BmOucEfwH9E3eBAZJBcpnhZXuC00wBVulfa2lM9Rc9AUd3k0zOhLpuqMeJs1tjelPsHeFM6OvYLmtDO+/fqyqKMRKNUtyPH7tYkbrxnhZMobxkMJO55x0Tf2AwGwR+NX+Axgd8DsI6Y218Nx0UO7YZN6d3o3ONdyIYcYOAtjFLqfNjT3qeA9LL0zeFNWm6cFN+1xJrSu1kOSrsyglsZc8myaCE7ZVBAu1Fpnu5e4Gsdmz2HHZu+hHa3OQTt8/kpEM+Fi2cqLq5bWXO2/O0ewNro++zECjT99xAvV08JaqZBn61qp3kNJgu1O8fbZM1iExVFvWzEofA4OGWqN1sl2tFB+9vb6Y+tZFjAhWoCrvEPGfwTZX7MWQEY0r1x8MPOHd5rZRAuUlIBJkyiIaGkQoaNlxMdxAbNfXHeRjnvOQ/yGU594H+NLUG6nWEG1sHk4KDrTjF2kySylwzZqsONZXaYlvjxzRlP3xBzGcfCnZyTsVX6UIv056bpYzL0TYfI0r871LrPJeKDVKf5Mz5FwHzR2HTUIs4cOPkJEB3px/4heuP6W+NZvINwcbRMES/QFewykXQEBVQj+B6hTc5Q6Fjr1x9BA59fgTHasuuIQXm8DwKu/ACT61LrD9Cf3tD93p694FoHRP63EJoRtJkfNC8iVJpU2aRzgI43dr2GyVuhtbcyXbd2e1avFeznGBUcttBiCqeocK5HgHJYoT02HsWzUaysOmKGQeFAeqoMYD5gk5wp73MSox7KTMCZNcY46HIvlgPYM2pKYPN3ePR5sFgjuuT1dSfNH/VprQgsNF1IGBFQkgiFN7mcABK1mI6xhaPc3AxcFMrTMBYB6bl60tGlW0lEr5OCI1zgJNuaZQcrmYn8Jjpo63sh3G3gjWrp/FjwgGOdDmm+cGuKoMGw3kRQFTh718Nmi6m3O9R7KJeTh7bV4OizeTveuMPXfvY9+94I1de8L5qilIre0NTDc8r7qbcv1tsyC33MiSUH2fGRJcgnS9MsUIxiVoVQqrUP2ic4Qo5QFEqBKDIiaoNMK4z7W5GbVD94W+FDFUxcSHXAjBhxP/wAoM9yKA+yyL5R93ke10vuGBGBWLQleKucPPgTgKCeOVjF3TTSmsdHftsb9/m9b4yCFdP9NhrbZvb0mMA0ELAaIRUt7Z2k+SDAgk+hlGd+kFIaegt1xLfiyJLMLiFPltiT3Faw13IUuS8j59gZ1dmOY6pT8AOQziAGr+ebQH10Dxn9I6oV3qEsXyR4P8ksG+ZrTZ1gCB20CcXxCgtc5ZPA6bzeD1zn8NuqLXQqiRoqYdZ2yGcGEmlY225aGjlP2uFrd3Xq+S4KS+AmY/OLLDPAYICX9WKgYP1arC3ewUCnUKdv2J0J7nCCnxvCWZmDFUmqtKD0E/mn6w0n6MYGDvIfUMQoCqHs6JYSzCoroyUt08rBPh7YjR6EE1EyzDsO5CWjzSF3+9QiUezqj9TBnpeU3d+4rtcdDzYY+ySEqTRw6iEZsf8jgS4oj4Qx2cjQ4eTKvQK2RezNoQWfMAjEO7KevcZBwHM7BV1mRiIRYzFyD7vpMp4OOPgxZgloHbn7uXKJUWNVFCy7m8dFJgQf7bTnfJ1waNnVrsTklPvEH+IiVXVuOoi7GJ7pwIoeA1IDXWf64Fu8ADv7HerJUnRZ06s+8l42mgmHKET3Ky3lkYBg7QPBxGFxKDyE0TZPYrnVpuicKncne9R7UmCST/YPrIQn2M4eton5QYLcckUz2ZXzMPi2JkP7wIQlziMj6TGsK60593I8ywhI2+OxrqHBxzQFMUfYCwMn0+hmgNW5BA+KuMLDxVJhhVTjPD0nlwet62H+BZ6MOIyAnXvsITjG/TbRH9KcafhMS69gVLNcLJsn1Ln9IyvWCg7QFORDpld7OIr0j6jbIY4kAWHM719DpeK4hH2LEs8EhOmUivfAQBI87CtlWQwNCfAoiYUIX0v6Z6geJAoVrMxhq4X6Q5UeSqt6wQK92pHtP8EJCEKnsvWg6nwbaEJ0DeiAh4e4KZjCg6tCDUE7ec5B22VxZwWvV0KHYGG0hdK9vaYgDzx1G4bqvPfhscHeFjlL3lpX3GSLH7LsNecdG8cp4yH7Fy/uZiKkE+1UfwkRcth+KDva842AK9rN951/N7IIkJTSchuICCc1SCZRIOCBi2Yh3H8RotKh1wGosOR2ubWIP8ru3x2WAt3WfoUyHIJr9CUC7395AxPpqGI5KVQlJbBJMcvQBmmLR9B3oqsvIDQk4+O2HgIN1Eg5kSNgNSvl6pby+0bOVRbzvIEwCg8MNAAdHzTkdZepideeDBtpUPIcl5qQNmMFjnbjhNgaPPa7yFkdNTby1IK4XSE0GDB6Ok2H5jlc0a0H4LkpPcJLBu2l1zjvTpWuKj4lsg6jPbDgpfpMe1qcEh5TAna8TEu0fnoEI02YOLVbDLZTcaWKRF5HDE7NeynLyYPrZsc1ucWEPh4a8jlrLs81DIa79vj7bMu7Fm9dKYf9f32WVBrHmAQCnU71QCzVLSh1G1s/MYcGwoxZILvYnnvX1cvxiE3kp7Ukat+YfA+xKfDRq4rdDaBvxHoZFl5mZ9BZdk/JsqBGEwRbqUPUeyRMtlzzRqlzPSjW0n9miZ3M9y/lMYaUWWi5up8z0zZDTp8AAJIgB7DjtmTifDh+SCivNPnZ8pIFyaxAPXdrLHMZJqL1K2Ct8p0srgY6PeO0M9IEPE1zmIpJwv8Eyz+83WEuv6YE7hIMckqdZriloxOrg6m0tNsAvyUrZN46dQbEPpIOa7y4j89r+yjLh/dWNDEAHlfK1RDnS/uwqZ2PwBtV7qKSkTFyRDXagQXdRsIwwRGyEmiYDJy5jfEHZcFD09Uga89B+tSrHGCW/HKN4WFxHzUWo6hvcgGQGAuYkdqC5F8dZq2mKvewfYwZWIu9jzHvqvkca7+edZbCOEJn1vJjYyyZiL3dL9rJEspcJf6otRKUONDwWxXKohmwdZfzyfgMX6ybg98TZAubVQutj16lVsF2I48NL/eLWt+OIr8wooD/i29d/di+v6De7v8vlU8kTMAfsae/6WtPq+34BO8DK+j8CBV7SmMIODVjovBx6OIRAb8dHPZIMU0J9YsRB1paoVazUzqVAh+49oUFq+cr2mxl9NEMzQUuReCbh0uuVgDzBY9kDEd6PBqS/nLUAldJDcTliiRI6JPd8IvT34LzrgKMGBsbQiWqxozZHzUTkzbfiFlHKoSTchJgnNsXbpHr3s7WRNmu02qmEWkApnjYZTmQOiHM/0k9reLRBT0EUCi6QOCegG+lKG97EZJZKmeVGXojybKdhC+GQxFHP61twenSA9gDx/PXQ7G5hw+PdgJHrAgPn5O0tZjWfN6kWi+Jdr3g3wO+7XBzr2cJpJdySEJ2hhg8nO/PO20uFuncEh7kb4QkFtJju+S9vr5pWXAAKLPXTDFVxncf0tIAAT6JUFxgUSLjJ5KiFQnxejy7QYlwXGlJCsyyuuLpHa5+K2i1leNnMDCvuALXtV5qNR30c7k1S0a+v7zcOv8PjZmAf2ulEIz3BEU/ddRiSQ+zoCUNisF6hSt2bT9KZbiAV4Y9gMMxV6rMzDFnKeHK4iZibb3ghN6wIqBsBQykYiIe1XXl0kzwKqp3EFNymhQ5Tdf8YD0dgOh8n47VG3wC6iYbr8b3lFWJnc71bKceEYtXbkOutL4Y+zz4tVA8XS6y1FD6c1+MKNTtqz9Liav+SfsTE+6gbu9yfSoMcnZBf80NKvHDuXOoPbTu0vnQ/jgS0cKXk/pRIj83YIkPDy8rOYznkXLzIpxYzueQXkkqe/sPEXt6sh1PYExzYuBTnC2beqZvVoWVYGewUDLtVs2hP79Wo0tflSqbiJH1/Cm2HD6BPg1WR7bxlVw1S78xRXgTzGguI7fP1IA9Xm09qMsYrK0qc+AC7awshzJ6TXVqZ7kGOvStpR3yGi0a4keNgnEa6OZEuIyLwmf25P55IOgXSNtejF3EqTN6xFGVov7FKkN3LxaYriOx+d6c8arbWu24mNHdwB0huyQd1mkT3PJYx+cQ800lN7l1JZ5ceVG3ImK4+j2zzScp67706/8sGvE2i430mW8VNst767l8a0R7Fbelfa5FXJ6PMyKv5+NOYlrEqU8Z1BLtFLamELx1Rdq+MDmQIwEdQqyun0xdiefk3BeBrgN8P7EgSgMtyxXiq0BCDP8Uf9jMy6uc2w6kHd4FbLjB8883wWBYwzR1J63EGlBQCTANgFd2FMyRNnWL/CyKOWcKtMYsl3IYTVQBbiXju027eJhBXzVU3FhB9ux+nKCOGfQ3WMW6MwArmocuSE3IoYehLKFmZkd04IwfDFLuQEyI/zDFRYmyAWodknPyz/plQDwasJZovmzDIAeE5QbSPbIkoGCP96EpzZIzYed7bgdbZIQXb3iAjO6MwhEdqrVRWimxBJ0zBm9VqrlnBJFoGL79whJOAbxmin9FilF7dx4nflieHJdTZmdPtfVoFpnRS/d+w3xZsh0CExpx4+QckD/rp5T3apeV90aVoO8fzenN0DzOgl6gHWJSRQ9tchMMHmtQbQgOKkefvLWzQ+AnyXSi2fr8r2RKQ1qIKDcee0L8obzukJiWixfY1S1y2qr0icDl2+ALa3ImttiMQEAjxMDUWW0doENCmCG0iSvgOheA71JB3PDaVK3hWssMMr7t/EFcvGM1+Gw8Gh4sHtiDCgXpQbRYTqABIR2NpJWLsJm7P21Q/FqpwUguEc7tkydZTA+t/qtD4PL0NC7UsGvWBD3oL7qbF9Pu6tbJoLVLyjtMArQMndP27UmGW5hJYqL8PHcytuPCur+AcyVW+IWRRvetLEhtEIgQqVyA3jWK4Cps1QVJT4sp9uhYLN0RkUhPEQmrbrvpDv6KVzbaFw6RtobFlWYnlgM1+fdYLhg/9E5GDGtwrQY3EiqxBgFlvpMpmCmarRTYjyd375OCkR+RwcjwiuLDzZeM5wxQcrhZl8DNlH2jcS3WkeJxWtdjqVxdZ3UeDI0vUOTb3h8ELYOboPhUcQNx2qvg5Yb6KO2s/CF5AWVLdPltoQOT7VpMy1RlLj3zfRjcZSmHWPKALber4uD9/goFjiA3T3nmWdXKDo86LP6LHo5FDERoCpCD9CdICtScf5rNffgjRlanWmIXDyhrubRJvnHgDt1EWasx5biVP1GqhVLGvAvjWHhGm4IWFQUdhML0wdKH7VGywq8oes7mqbDGLq8oasqp7YlfQMOY14DxBC9n94nVW/YXpdQalDeC0X1Nakv/K/nZYQ4Ei8xrK/L7z8YjiPaTNskdDHdHwYYKgvAbieFpdngwi8UPdlpDdEnbGLlBLOyyldtXrNNNmHGpRSg8TZRQtbWMVbCEteXKJKvHa1VKnMkgpsbpDbeHh0tt1LmWyPGaJXG6q3ftYyqmRamMuUdseER6eC53zZuUJ62PWyN1WU+0Hj1lO3WllFKbuAhLbsyTJXIXG1T3VGjKc6MaPzwGcoVzAY2gMDRMGRPydB4joYzlA4kP5jG8rdsH0VXdKYfVLe2HkWfAvIuwaQ+MJiPl5vnzOMcrc22/Qh4gtiTLlIYfhIqZEFp13HA61lPJergI8lRjMRQbN02QdQ0RfOyek5mkzqAxNVuUUb4BlLqLNFAiEpo9rdIrVnJwhbubkXrXIntdA2+h4dzOtjN5QlsvTGxrm7g2mujx9iN3bF7RRUtBCLZThZFN94uATZ9mrfPxcwa6DZGyUq2ps8ArZhEElfnFc9tehLsyApwpX1ejQJ0oFMEQsXamwxXr0g/aEnT9PT3TqPTGHe6otZItWgzpKzJW+PvT6lKps4A8eWwZg1CfrSqV3sTYDmDlKAoG/NoOy2kQM2G6RWY5JumihR4vEH5HH2CH9rZAGrwURoE6dYEx0hl+tGs8fxOQHXHG6+CTxOeekHaLAWstRgrN94oLDPASWSwus8oNUcQStZKtdmeU/HxpZbLLxaZGqbFNoS8JzU7/TK5rjE66w3VH7C2yERdnAf0HY7SC2cxpbhCQZXPnsrD+3Tzx1F4IZWomdSnV7bCF44KD7qxB0ZLRa2ptb2ukPZMxSS7tzSzvUJizIUKcW6tCNE2LjXFVE7VAXgFYyghfTeFCdpQKK1ebk8zH4rIiT
*/