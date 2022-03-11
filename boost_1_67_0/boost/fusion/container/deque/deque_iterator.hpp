/*=============================================================================
    Copyright (c) 2005-2012 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_DEQUE_ITERATOR_26112006_2154)
#define BOOST_FUSION_DEQUE_ITERATOR_26112006_2154

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/iterator_facade.hpp>
#include <boost/fusion/container/deque/detail/keyed_element.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/minus.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/add_reference.hpp>

namespace boost { namespace fusion {

    struct bidirectional_traversal_tag;

    template <typename Seq, int Pos>
    struct deque_iterator
        : iterator_facade<deque_iterator<Seq, Pos>, bidirectional_traversal_tag>
    {
        typedef Seq sequence;
        typedef mpl::int_<Pos> index;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        deque_iterator(Seq& seq)
            : seq_(seq)
        {}

        template<typename Iterator>
        struct value_of
            : detail::keyed_element_value_at<
            typename Iterator::sequence, typename Iterator::index>
        {};

        template<typename Iterator>
        struct deref
        {
            typedef typename detail::keyed_element_value_at<
                typename Iterator::sequence, typename Iterator::index>::type element_type;

            typedef typename add_reference<
                typename mpl::eval_if<
                is_const<typename Iterator::sequence>,
                add_const<element_type>,
                mpl::identity<element_type> >::type>::type type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(Iterator const& it)
            {
                return it.seq_.get(typename Iterator::index());
            }
        };

        template <typename Iterator, typename N>
        struct advance
        {
            typedef typename Iterator::index index;
            typedef typename Iterator::sequence sequence;
            typedef deque_iterator<sequence, index::value + N::value> type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(Iterator const& i)
            {
                return type(i.seq_);
            }
        };

        template<typename Iterator>
        struct next
            : advance<Iterator, mpl::int_<1> >
        {};

        template<typename Iterator>
        struct prior
            : advance<Iterator, mpl::int_<-1> >
        {};

        template <typename I1, typename I2>
        struct distance : mpl::minus<typename I2::index, typename I1::index>
        {
            typedef typename
                mpl::minus<
                    typename I2::index, typename I1::index
                >::type
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(I1 const&, I2 const&)
            {
                return type();
            }
        };

        template<typename I1, typename I2>
        struct equal_to
            : mpl::equal_to<typename I1::index, typename I2::index>
        {};

        Seq& seq_;

        // silence MSVC warning C4512: assignment operator could not be generated
        BOOST_DELETED_FUNCTION(deque_iterator& operator= (deque_iterator const&))
    };

}}

#ifdef BOOST_FUSION_WORKAROUND_FOR_LWG_2408
namespace std
{
    template <typename Seq, int Pos>
    struct iterator_traits< ::boost::fusion::deque_iterator<Seq, Pos> >
    { };
}
#endif

#endif

/* deque_iterator.hpp
4aqqjABwj1N+99TsMp0lDSfem8qXqpsa6+A6qG0OwsDPOymBjFlQxRFLS2cmasYhTatrlog7qE7Anhj4A8pW8jBicqKESMIe0pq4rkPK+cjnoqHHgF5etErbjhTuvmjDRLtiVdbQ7YRLGM4JmtqJS8yOPphvBLxh0buhTaS3fHAhkriNQ+G3AhiVuHHFLUW8pLLjChRzcNfCmpWdjkutB2vX76jG8F0RRfTygPMCkVIMKFErWRDzGI60LClD+YactkXLUI1d4lYQ906omj6j2ZspBI2NUe970EEFq/VsHgGFXmiLSobQwqxnuQ/JDx1nbmdeSSOk1RBL3orwzIFPCN5hmXvGT6oesmv7c844OPv4TK6SVbVTTUcBI4M1OXUG4eOJmqN/TUJdZc5lsi0dnKtTDiOtSFtt1mUduMYz+l0SWH3AoF6XreGYGQqTbsZlbYgI+4FuC5F95GzQMSOMuTMbt9KfrNjidGH4Z0RY+SYY7NI0cR2mbF05wwswHImoc+SOeNz8tPMdVceoze4aQ8tQFlVNW+smXgbMDRvrBYCC4VcrVy1XX3S0+qqYHpkoteSWGBt9z7Vi0W4wMidrnhQ6wzEPE774UkKFs/qh6OTNYV77ra/Si/b5mdrTBn2T5M7a4J+rN+j1aUxGlZeUDofo7DLVCfjlaeYVteFyMqXk5ss4iKtowz191C4vHSNbGdYeW0oycw+OZdullE+QXgojruTayazbGXtVt80eeB91bON0/X0icRAF6InR9XOKfCsImzAtQ+gju6S62tS9UX0sZYYIGLBsdciy+wSQRVJmpOOmmFmQcaoSE6cej3+7hAipFsKb3tXZl9Etsp9IJpsllUO3+q91R9Zl1m9WN4A3IfSoVcFRJ4IDgsLXJJ7RngE5p76HMB/IrO+vP+W0e00egj6VuqNtAlZf43UAPYShJdl8O8n1a9EpiyOO8uUv0U4Giedm86QzFxYwDg85Qaehp/GyGHq3cabNUrteRpPruwx9ebuMijdhHx4SPbascjtOw9zrs/NOTrnfG61vpO60n7WfWFxv3Ec8O/6xRDLyNBKAlT4w5R8PGOM9YDgEuy1H9s4IROINndwZbSYLIWVwCYD1XmaKjEPksyj5Zg+cgXAk4ebhK0NXZAlXsVnQ7c6AWcQ4TWEazNSdrKE8gzszYU1F1xtvHnm5YuKNlDyg/R2h8rdLebjyhN+Zgb9b+OQanJDCJTkPN97nmZMmq+WHj4PAKM1BB0FkkqFCnhi0yP/XSd0cqrVPaIdINb90l8lECq1vFuAwvlbYXKHKOnYFT8bcv3V8bY/mRvzNdqK8d+nKlzdmipkeZlzQFsuLmk9cClLFVzGLqRjMkjtlCl3OxykLehir5SvjMQXWyiwSK+p+MHInlPq2YUsmNCrLkNApVkp9xbScA6sfsIaQDO2NOxS+6jpamrDGxJIwZeyw5tkcS+332Q5ifw7VHV6zZ+QJPPmJ1ZlsCtp9TS0SSnDXmErBgxSVhV7S8ZCJRFKgSwKTSK2UvV5mPiCW3H6xSdPOeSi2MvFs7D6kTX441OP+AdgX+WdAlq45Opb7ftLoWL0+rVOShyAnLuGQi13PJbBSCcYKz37gycAXw2fFqnOky2ib17MjEUMkA2HnB8OU/R2oiRUccN7LunkgwI6cx+8nAAafciwlEJClE9ZO5u9AZYCqyxXnSAOG5ysGq2FqJeHFhAhdxoAR1i7wlRHpmhqBOHGKhHPCXX3Jv8QxBqnnlIBDXXah4/G9WLtwX+p/8QlHTOwK08kOR55tsjRxxPZBmsQrowxt/NbJGoZBm/guY1v2NVx/4ScIY0ukBZq5KWlHJ+7TO/FhUYrPS9/LEXVFW80LCBQ9lsSdlMXkhpL8YRBq3MuFkmDaqnowC8Eq8ClUrhxNLt7emb9Iv6K9dXIWVB7h25NtsMSgOgI6ZcHtBdgMA6bJsOBHmsQF5+MbCe3o8OTH+OKFg+PCDt3qkzulxsWJD6siDj120ZzMDDD5O+YVd9HVHNGpC2UW1BwRc0fN26O/06wLSk7Z3YO++SzUYCtZfJsidK8rm5eB2pM3kp5VfP/uAAcvGkWteVHFEwMAuyHfsvBPIlMKBbXCaFaiqnpUltu6gKy1Fl2X4uCUfJyTPka452mDhb5SC0X+gGeWmwS2sIRw8G4YBFtgQ393GzqaXAmTzmG0AqIETQPXd2ADsl165Oeol24r5JTXLEotbXpN4ZSWfKx0IPCVy0X/uSWNVXkHRsMAkKvr9Z7gMdoZ0dbLacBTxdlO/Inm7SWfQZsJU9P3I0P0+YOFD/xPmdh26N06cGMB50ba/gvx0t6lw8OPHMd5pm2qcfGOQ8rkDIhbC2/2G8fmh1xCJpY3Hqi8SuDCoaKAe/h6Eh1rWP12mQtTf26GTUpINI7EGzkgKwUQh9fWHr88f9G0ZdBrJGrpgjl4rQG09qbchAmKHu7jRyOcA+ClnfnBJW/LlJbDF66A8BSdI2w6t6FXnabA4hSMYZKuoaiNdjfZ5eA4lj0b+FjrHenhWth41pYyWsvkpS+S8shn7+Pvwk+vBpTCYLhhHOEwQLgV7P0us13NwrJdZrfLYZ+kdCFyLPgHP+6nzFvwpLxMWZw5xe2JsDkzXR1UkwqOfMmS0migmMJU0/xWrzy3U740mMcTOK6xUODrn6dh0EYA2rySy+Z9M1LtpnmnTqleVsHINVsqyOEEI2+Qi1DZS8JNd0+YHan0BLLQc1H8H6mAz5bozL8xc4xM6+dmReoYy2oXuBuwynBS6H6mnti21mAaAMt4wyn31J6kvKOMgxH5mpN29/jO2nGURhrMCO/a1dF8OTW+aM3+NhvnvKemNnUmjtCQ3yQYUaiEOYjD6W3HQg9GDsR02wXHb739cmyQvGEjQCdZITv9Sa8I3dEWccWFILdXFG0SGmo4VPpKAJxmZivGcI8USV5T/W7wPIqRDt/Qlu/VD3S6E1j2CRQhq+NLOeYjE4/aL81AN9D0LIIfMEW+Jz/R5hnwArT7vlY+Bs2DcNK9Za5o33A7MtLA8KZ8GgtHjrRdEhmqVlUhlU/L9BV+UpZWpOucvifcvfNrsrWj9rruJn0kOL7QT8cBbtGMw2lQlIFH0yIlf7g8J9v2Gn2d/gT/45aNTlrwu+oEvSiUOSJ3E9+GTh1SDHfXhFVYUSJtwavtOuttafDduQQx9hrlvMIIEATqVsdDLw8pLniRA16gR5pUHFV94SvGDEc7SNKtQtalxwKMeQbmrALHpk0mAfyjVZJV6a3s9xT55L80eG18sn6g2/TwJ3LPtMmG3SN1Ss9ilUQZ8qIP7U1EG/L0G5ZVSHKXGJJA6RKFVZg0hP0u1i2EY0bwsdrZGQiVOb4n4QaAoEXJC1ArR16HYt+41WGT+ZqkZf6qaOSs6R1jBh1F3xLikgfAVRV/snonjXvSNFPu6uRP6HBWKx67otWTmiMxt9CFqlSVWOrTnDNQpWFPk1MvV0ytD9A40353lwdAhxh4BO9QxGuDJ+YkLxUckIi0L241eHLjCPueJuAG5Shfg2EdVdLRPZIb0DJ41RJXkzL79T8XFtuLt2sBF8hd4UJcgLa/cxmnXTdvMl33eI+Zpiz+Sc8A95BvcYOA+bT135Y5eidrLr7Oer2m21AMeom9vVrjACcc7HO9a4VI0J/eVI955LnmkJMRzLsPLr0XK0b+7lpeFbj20H4zmH0NYOFAOyzCVbJE54HfYfVTUwgJHb4R2CyEdnAT8K9DyHwpV33q+tSV4wXYG26DbkCtAzToehqhNdHmHH+fYV3IKxG3532CJp35fgR9YAkZOj06mX1BN7q4t/VuoHfh8X8GtptGhhJ/vtLMFOXFXcJwwq7fsm/aJtMYGU/EqMXVkyQv/iSVXpULhFbxHzWHa67ID0YMqo+PHydTuatK1kGNHTWp648xt+w8sCdcVp+8fHB/uGvX7OjI7GhjnESmPWQ9eOnMJM71TLBhtTuGjGMg9SBcs6HV+H5r+u/s4sc6H8sOLcJJSGMt0GJIHln3vkkVCSzBchyMTHv/uwKKVPENjtlbcGXUK/+7Rrnkw+KJSZ8ySgg96nQosmtL3xZAFcSkBhZWFM8loiyYwg09VRPdKaAd8OkVYkkSAFhBeVaTp4BTVDOfemdwTHmRBPOBUiHrVorONuMXC19TdtkK6DuCqEl0emZvzWp7xWIC+KUXaoxEdowDCw2FMWBzgBRYE+jVD98/E+ujDR1vIP9lItAucJOsa2DpV7JL9OkfppDMr96yW8nuMR2nwNfgM7XGn81vDqhtwGS6AedUe+wgFUgixwjsOSnw+y28wuGfsxWyeNVP+K0ge2DoTa4z/QE1ECQrZnXXr8ZmjpPpMBdTFC/f6iY9upcq7frX2I4ueqis15dgtm2CDd1emCsN9KQ8kwvupD/uvpCnSET+oLRsdt6+lEvsT0bp1SLNKRHKImJ5+jtteXJ5iTVfNp8lANa4CH/HqCH0KtQzwwbE1j77htJRKSYE7CRY5kjSgr3fLPuKrwhucMNS79cwRnlIhUzZDH80+rQMcJfb7PWTVG5CLGKULPs5vFcqQWMuS5wQJj3WuzFuHRzmiYsQKNExJt+UU28pFkntn4+Btn+B2k0wPrDo6xE9IyF2KHQdqDtDXWKs8URNhwj2FIUlTPa4jt8ovuEE9YGb8KpskO/f0J3nO7l53SRHucDNi6SzgxDhBZ5lfOZMKHBezGo7PMnyoIusixjnXEtiGLNaZ7iNwFfShOsxcLkDfCf3p1GxFXBzI2cKu0jBkeQGM496mhg2JL4YY5F6w4x2sxYm9Bj/UBsQ61cgj4EeYusU7sf/ij3bzVrqALV81F1TjZX77ilVxnXnwIDyxihMKRxVdCujlDUH3GTJZql0yY2xse7uq9JkawxVnYS3cdsG++xGBwhkg371jG+FNGMBmLmUrMsuSB2AwbqQFc6BSKUbY5zOikwp275/pWOOivZYbJtPNkqr65gyFTQdNKmtY1+pnwJt8MlNNIo2wvoyQ9qMJXSi3rJk6kBzsSJxgVI37njy34tRmMWJE3HHEhp+ePRaks8l1RJhQ9D6g+ZgiUT6NfKGqIocIl2EUQtB2qErFieXknoHPZMOcNdSOw9+1XE+5vTtDuS5AkUHfmb4L/AXRdw6a4ZP3OF7wugEJrtitfABuQNfjaY6kjLPFobE4c+iIY062gMWHjD3vnr5HuL57aWMgqluKN9Tm/GlyScnEh6BWHCmQhUPyyKVmp5Dq6rhNGWqC1uBzFAXPcuBl4GVB7n/a5JjWAf5XEHR1BGGzwM+E3Pn4E6YzkWbk9QtapntOPtyJNYSziminVd5rNLUtMMa9pOjQ7+PoH11gmD0CwM5QaoxqvRj3hlOpPPIa8gxME+zmKQuDjIz0maAk5AhzlPk94EHqAmTK6YwoWzIW0gio0waSTJJREuCHQf3hQVupnyNIZyo87Ok+2DHgoRjipkyUvHDswzxVgTG9Er4irIy0qkzpvBQ4k3COk0Ge/cC+UuGy7CHrURy2G+Tu5Fc/szfUuXv7AG9fuXAp4A2Hdiwm9krKiYNzPNnNMhWb/a7odXSGqMlfaMXxb8DJziTMP8C01WT0QRoq6JmHZYBrAQX0B27KDqoMC5vG6D7IatdQKuoWk4HPMc73xoYJt08kykw2I/ntowEoF2OSJdeKQGwTGHwgGOKZ8rOFMCEOYUJNp1EilJ3ns+ivAmkyWG+3Ry4Ealxbh1ZjNxtvaZJeJ3bdxLMKuK5rlmK8kDqdbuTclcBdIs5Nuaw5IHxDUbsUfKVyxu60O/Lk1hnKOeI9l7lVVmbAh2q2D9q9y8ZCAwZag1gCATS35ohCA6+R0y9glopMr9jSneVKlupVuJGiCp98ORRogCAi+TdNODckrlQwYC/K1JCcmS4RXwXK/wnO/7dguB/T3KEmGPvbPLATyFrBURSgSgv8QVB//QNnuRa6iA8hGrqo9Tqc8pBlTtHtYp/ijT+qYFgtIz58OumVw0IuCX7ZIcbkcu1L3NlyY5B8zWo7r+4JbGdwnFl5YEIdwFiOGTnFrQG5NXez1bk7W1nPRKELRAoDVuUmL1lOPV3UkR64jxNoWbiR1uPWOaTyOCfyWM8W3pUtu2BeofREmX19cegO54EEBmAMWBIszRm13UqvP/7t17ETdsNqz4U0gLSyxSgwvhrFTI2CDVABbV2R0CSdzg7JNI7ymu423hKSZkCtNUvh4Lvqc28/ZzS1ARLMUOJE8CPVFGqHNy3k84asbBYJbNuHRuzC/h1B6AJzdGNmSlRbzfAYClhcWFR/LxtdgOtQqV0paKl1AW4O7rUx99QqaY7zxusSrOa3k/EGlibS6cBAKFJuUFKIZ+94E2cUYETbX6PxhSUtGl71pjtlGHgTcibJgf4y4na8V7h063bz2bf50gDAI/2zaVTkw6RCkSjT872jyaojd8fNr1YOqGYRDp8zVQCT3wiaMYgGL5/NK5egExRAqMfRbvv4EGEAk2ywDSeajFZxnt5t4quxO6ZQd8O4nkXWAQKhpBWPfCPXi6BCMBbtnSFAX+ZoO7PDZmUYkocmfCohSRlcdUDWICqnXO5S2Fw/HHvCB9HImZxsfI4twMsPzRj6Az6M2vBjpQQUsWIUBF1Agy8ZRQFUj5B1w2h8YdEclu6al8xGpbpoihfMa2HQRc57kKwAVerbQv6AmxJCg8kZDdJqACzmImzxFX++K2TJLgVEqmRkMd+23UJAJ4h4qO67saI5NOlesBIBKeZACHdP6p0DFZTOmvSP6n1fg5WbAVA8BLAeOJjfHKjdebFkgV/qkGeNUSbBqdJ1GKz7UJk8/kNgO+P7d6fsQGf7AF9Od0ZtGJGNPgE5ujbBUOlEkIzYotHExj8nQu96Q09k/nnpb+OpLAteQ9rxq8GTMtVxp+IhwJGE/uvSK5tkaEcQf6Ev/xPugqO4xyqhMCEmccuRD75aZHfo6E7VBbce44o2iznqfyp/1Lux8qp6KPCOnqiTh8bI1WtEREjFDKv9s/2NMfsZ9c/DId09gkmehe+ix06VAmLIkqy7tduf1dhmc54Uu0+SkVU4A6KJF7Ki8cbFjFVdgt48xjV8CfwoZxJab2FNRgWeDYSbVjOYeULhTfC5zJXPeKHr5l7fZPLcG67Exk2l+jpOXYO0ZNT7KwCB8f/07n7sfnX7MdryAA5vxaI7uw08zzjrUfCHI9ybumpl/I3QSLMurRCDw3eAThNEA0ynJ7pji5xvIij6B8FLXZIP8JbCfeWnA9wWaFsXZFMcYFQwc/7vz/k4ks/QE6N3yrjbnfQT18LDuNVVpgU67jHLFlcfx9+J1SVhrdg+UhoJ26q2GlduPkxAmhYQ/m0Sf+rn4mKFMQda/d0Fxe+tyO7lNi1EAzJjt5NgScFZnRq1sb4KDjiy9ioVj19Ix4SDmIWJmf1/BJ9Vf1E1j2/zUFOmMpMjmvZyHCpUOVTXlsSFrt0AiYOI2NLRcfy/hXwpzpGQYlBBKb5GDtnY5BgKaiIG+Dy4TxIn4dc5P4r8KfXHTiKbbSs/Ft5mCEyi4ccncLGiMG/Fm0gRtTJRkbi5RMagpYUDg2kHWtgkXhsXLw0pD+Q3BSR3S5+kDHYiH/+SdWkcza97C+sbFX00LlVV+qkJP94HmV3HTGucG1jIDydyd60WlMGBHtQeaCj1jZOn0YHnEhqiat+tfXJdEZPmWp2XyyqdLEOgmPWXC+4Pr2YsSqUBytZpVe2uV2EXi2XPqpetHV0GdYuzlepLZFdsOXDRAGCaLWjixfZqzABsLtYEpo1e/1TV2dgtdWVVzSvf/nneld2C9RVEP8nljwzbltZ/oz3kIEI8G/fMqm9zGG0JjQ4MocJZ5ePrqLEpw4uKx018xIlRT/WM6HGHf/XUAmdMAkOODOdyPH+9/W+d5vf5C36OaH1S+zAPbJGHq6QC1vV+xIdNsq5oOteTK5hboIEMaEMHO9VpttBdJqDUsGAi3B9/hUH7QIoi5oEUlbbybadM+KRSnvnRNc7G6/PD3oI/8ZNDVd/+fO07nyrU86WHK56T6vx0+62B6U0Cg3exuP5PPKbLoeYu9+mvou7UNhE2XLGmh+D86D/I95OIMuWDcNkm3ansULrWbvGRjT2EjUACiz10wf923HUVrWKtBUWT9GeYs1diKTScIpqCYH9WS8x1rUK5hPKp2c7ZpIoJ4fK+8q70TYth4+IsrGX9yL5RlUa0rrxA5LC8dG61f3jljzS+wLXlYPL9a4JaLwVJAk0SXNQCE/TDm+zx33YyoxzDQ1Ti0Vl81SmZ3GHqH7z591XyRkNWnump1gUfA16sIa4rg6zp0eXyc5sAbfKjiouw+DL0BKID2P+q8GzEfUXEtLwGwLLqMQmXTMDDlZWOmpWfOltlFg0SWVcUevGaHnGTmTiaOhgWt3d3RzOhR7QBSISPSV1+mmUexhnu5pay43sq0hJ4ZB0VFQ4Am9K1CvIk7UO78aLS4SmxFXuvMd6fK/iOfx6eIYhuNUPoXpeAofXP5WsRk7TikUhEgJzk6nu/YYT5J30SQ3NdMYDObXZA6yRDrwsVDvXC+SRYLx181Et6Ln92reJ6mEtExYnXvc84i6n5ec38fSCim5mTuQHpu7cY9vQFRqfqwbgFBLpc+KNT3NdzZx9NA1WSxc26o43I91Rq4cx6gDsE5VUZqiScetD7GymE+j+DV2v5KXovPCcUMWGOu2TeXL7piP3ifDhVD/inu1q9frJr8H5bnYFeFoIrAymg9JiQ77pQUxorKnjoBcRHFbxSm8Xhl33ILmYJmkMFbcUaK95DRYkE9yf88UH86fvvG4sbBKU57EOpO9LveEDtw6CIsrsqNPl14aFVJyKmaux34dwD7+B1EVkEa07mnzToGo7x+Ez5CXcDsVI642XIvgIfIhOJNiWMEEiVqbD2jZU+B++UmjDXM98lHPlJwZFN487St18xWhPAkIZ/qQsLb7v5H72aDXwDphy8V98AKbliNv8sZggEEeOv9VX2qpJOYR1rs/uMcyiTkXzE9F+J880kJKdepfNzJ+OUxQVHfcIDTsh7TCJtR43mWoojXnT5PPHQbmXH2oMcW+u5BkNPW1uVYdbb3MW/pm0146Q6Q0nHxA5pNe8W9wKeN5f4DHCnm+sR0+sI98HYmtjbzM=
*/