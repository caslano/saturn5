// boost lockfree
//
// Copyright (C) 2011, 2016 Tim Blechmann
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_LOCKFREE_DETAIL_PARAMETER_HPP
#define BOOST_LOCKFREE_DETAIL_PARAMETER_HPP

#include <boost/align/aligned_allocator.hpp>
#include <boost/core/allocator_access.hpp>
#include <boost/lockfree/detail/prefix.hpp>
#include <boost/lockfree/policies.hpp>
#include <boost/parameter/binding.hpp>
#include <boost/parameter/parameters.hpp>

#include <boost/mpl/void.hpp>



namespace boost {
namespace lockfree {
namespace detail {

namespace mpl = boost::mpl;

template <typename bound_args, typename tag_type>
struct has_arg
{
    typedef typename parameter::binding<bound_args, tag_type, mpl::void_>::type type;
    static const bool value = mpl::is_not_void_<type>::type::value;
};


template <typename bound_args>
struct extract_capacity
{
    static const bool has_capacity = has_arg<bound_args, tag::capacity>::value;

    typedef typename mpl::if_c<has_capacity,
                               typename has_arg<bound_args, tag::capacity>::type,
                               mpl::size_t< 0 >
                              >::type capacity_t;

    static const std::size_t capacity = capacity_t::value;
};


template <typename bound_args, typename T>
struct extract_allocator
{
    static const bool has_allocator = has_arg<bound_args, tag::allocator>::value;

    typedef typename mpl::if_c<has_allocator,
                               typename has_arg<bound_args, tag::allocator>::type,
                               boost::alignment::aligned_allocator<T, BOOST_LOCKFREE_CACHELINE_BYTES>
                              >::type allocator_arg;

    typedef typename boost::allocator_rebind<allocator_arg, T>::type type;
};

template <typename bound_args, bool default_ = false>
struct extract_fixed_sized
{
    static const bool has_fixed_sized = has_arg<bound_args, tag::fixed_sized>::value;

    typedef typename mpl::if_c<has_fixed_sized,
                               typename has_arg<bound_args, tag::fixed_sized>::type,
                               mpl::bool_<default_>
                              >::type type;

    static const bool value = type::value;
};


} /* namespace detail */
} /* namespace lockfree */
} /* namespace boost */

#endif /* BOOST_LOCKFREE_DETAIL_PARAMETER_HPP */

/* parameter.hpp
vUQqGDfCQffAoBNWwX8qSctLCUHvnZCFCIPD+SvQgmKrWjLMeq8hQSlmdyGoBeMK7qYpIquwscBC9yMYodbv+RtQ7M5yAnbLq/guSJHPRHXVIsL8EBd2Nzg33emyvVYEyv74K5tJux6J0l/7uwMAAFh/D4L8qPZnAIBBsOkS6plY9ZrUVvnjL7XepGHQ1H/2fhFjTctufViwCwmkqdGWdy8/I72tlFiL5QIk/l01l8nJErQrSCVTBOn71wBHYUlcZODQ9AvgwGh/4iP3EMQbkIsSta9hd/Ktfdkr/cJDIDmMuhZvGXqGZQhQhhlJXuVaqpPOFgmyrRpxLnB/EgQu6DibRrOqx3T4hSRpqtNArx6Gt/dtRzOFOAMUWGaFB2mp6iEJeUeSrjxc7tPYUnf/IEF8ZNJ4YQaHePw3aEfk8cLS4f5jtXmtRAVFEQ/Y/FSLPDW4pYNAb/Wo7YGVDgtGf6WxFunUZOpYNqcqHbqi8+sqzCq6GFjuZAcWAOFyjgV7aY3kjRwZBdlR/xUAhoNRX7WKfmbY5R+9iR0VSEnejtOEENepnXMNdIXeHzRQe7vBKFtL0m1NQ2IjxCBwBVpILQsAnb2n50QM1pwm7VNUJYBzuKIAnO5wrahHDWGQg2M0yiKCuMe64mSTZcfDUk1XdKcDl0GsgjVsiqQyQAkeiJYiaqZda+nlR6WVypyknjAYPAG4vBqKl3cbeTW8HBlGkAmXIyviiuWr9HAhGboVDObhzIKsko6BYD8AUUJ4WzBqsbVRaq/qPZ+MKpjqqHmSatwuE7XTyVwtOFAIkRKiaT23mSjtlBQERJROrZq7wKDu85lAkrZlKFi4XHkvRCjSaAlqA8466ZNvwK/3oZZhJfkiSyc2G1DjJHBndBzFhLNL2rYUfCVO+kBCJYxrRT0eQcCmQXoKXvKMOAtW6W1jcudPVnBlWXCVOHHCsiYpd7tY3JuZgJs9D/Ni86S/q6up5yZaC7gDHiUKT+5BA+6o1oR+S/D22xJS4AYk4/Zj9Vi6JOVGG6VSyxoAzsAEaJ2A6vv8Qbx0mPW/ThAvLjYUrdoeHbxx3nEnWhPxvKNh3tOnb5ocsyTnptpkU51chSBqnx02VmPXkoqCsBA7KI4m84d/WprEn/inCX/y0nEY4DMR/nxCCYdrou/Y6ophiFG1vPPTcQRbZw+Gpk7imhbcJguDZKtoGWROi4Y62rC1lXY3JLKehLxq3T2JXgZWCDMgJPGWhlRZ/MzBXDuPzCCyDAcrrpT01gOmC6gz6OaBPU5FbGrceSH65cjZW97krJtPr6yVqKr8AilxMwKFDCTnDzBP94PiaGzWUoxL2uhxs32mz7vnr3hK+xS+LlfwOQaPAjjx1tFQunNSSGshEagulXg6O7QMz9dB07OEdQfbhJol/0HqjqnzmB+rblo2PjdImtuid9hk9hY0dGGNmieE0j7AT3gaJOECfPj6MjPbc8X1xn22mdaRCxLHxYzdjNanjXvefTGh/yyVAwJiRDuKj75PLHttcYGL/x3DkcMiw1YjC1b6mD5NBM3A8pAxkwkBDDqwu494woGLWzt8rHFagpKvY/EwAdJK8MrNWrYg7/MB6zwrRnqMOx3qFyvH6aorIRWrMnVdVzF95SG9cc/RS+9rtnOL1WxcpSQVM50xDagKAz99qAz2LPmKARIADcUGbAkV4dBVBm824PDi4w/S/eekYgRlHDWg9Kzz1s7gzhVrkymivmAwMf4yj8FiMxeMdOgdnuCEc9BlI+KsSgwTrzMuQXGz99d3gHCj4J/EK03fjMqsbgXfjucd2SxePtX6CEHr+FRLncwQ7xS64gIVao25f8gK6LI7qSW29dVu9VNe6BbdiA86S0T2LfnOzIEyESBRUQZZXJ5f+Bv0UaUxHaXtSOfi6lLevE1fwemocNnC3p8QVklshkAABpORFVxjeSFAdTKwESdXRHxQAwgAGCVfpUZ0x+bh3cZcSwmtIAUkfnVk6SrhT/Hs1yEXXTzIeD1JqQFAFtcyOtWf7XLfzVfnRz/1idD9YmeT8zJ7N1bRpY8gN2bMcNf8bCeWEWCHeYE98d+2N1lYt8VqWtQsR6L8FNCrn0HUJwTb1Q/cFXefLAzrP0vu+UB8JtLbg+e+pHSJdFU+5yZQvHYVGYI7f6Y5SAgGGeoNPfYaGFLcPFMKsJOlH9UswuC/I7+jBQITg0IaRamddU9HVPrpnD44/SVmN5eMYBZryf1E18kUwgoBacyslK5O2/RvSN15d7YEeZ4/nZlsBchmqzNVY4GtVLb30F9qyoq3a4QeKDEL8vs4H3O5/5gpzx8eJq4zFGSHxVWxEQryDCXRIll6ny+M4TcS1LFWXWgmw95au6zGCr19OlxFcvnSJapbE65nMVxY3KAARJopHcQkwcOk1voGq0ca6BA4U9U0jwRhQAnTfzbeBRM/umeDOBFqKteUb4x8KeadO7EeQf7Ljpds5NSa53h7h66ds/sHALye3nLDNussVo/He41HIpoRNDf71Ov7l6Llvw4dHrLYUro5qGYzFaTFFYhIkdJe1pLvYTMBAOjdQBwxeHWQeMDs5w1glUvFMFVSBR5eLTGGL85NFPTq+cenW7WoQ12EYQhW27uafO2b7lbaeLL7NkQSQJNMcHpC0ykbhe4UQ4GaHGjLLUxN6Csg+AAOcJ0RXcJUsus9jne82hiSYckR57GAkzbFHEXidTBE7A/6sn/pixLJrQIbkX88gX4qKkJgTV74m/rxIVQq09aE1/KHJjf8p6yJuCRqfaD4R3VNWx1FubWww9/Dz8MNPibPV8orwiJg784tVa/NqU5CKAYaowCZs52f53xoiBrke0Rdm/c7RdOiMZDBmloYNP9umpmZFZZTqY00Bnup2KBVSZ/Xz65c8C9TE+iIBp6MnNI/aHT/Gy0ooIBRoFAejAcCW+EVLRBc0oDTeUkFkPuA8krkS+CuEh7knDWUmzamyUhmANv0GAhcIx9LyYWsENCqfoambTste2VoLhN1heFMclU0YZR9Qe/40Wbe+AbpO7UNLhNZoEWeQFawR5PiS/IGU0TflOSso0J1WVXe/Sj2UqWDCVEEFcOtndE4dVY+lDdBDlKY2ZC7J/7Nog3rxkUCXpmrw47olG3WcSOSmK/+omRqACl+huMv3FqWIgIR1ZdxwqiocdZvrn2rjNaexmcFZ+Qjse1s35mzaxHE45rMik0WyqAZRIArxa2W2+jYkOl118mLugk4Hu1+/qOpxwmvkEVvUh6d1nBVnD39Ab1enyFY608MMcl7QGszNx3W6kWhoL2Lf49m5vMPW9IaUeYtNwIV8ZnQcGLsn4LywIsnRgtr/h5vUqAIzc0PrMksAf72qg1O4gM/tWoqKx1mCPAgdKZZXe1ZYmGK2D0esFuW5ZUX+DgUtN/C1r4Lk8yqbk/pHLldJ+WRYAHdDfSOIpFNHqWFWa/lGRSL3JyqIQSu6lCj/GKYg+M194WgGiY3gYnSOKZT/qCA/koKfrbaCIqTIWmj77D9Jb+anTKzGVHeRljYMVqPXdl9QHZUDiTb5bKmmghoAo7zBpHgJFjzspjycoWKy5bD9QXoMCF1q7iv0KeBsF+QEmoiJGu53aImyD31dWKG/4ov31SJjxmzlKM3Hd5WkXyL0FQPqVKj5csSnwQlnAKFrD8kMAQNZ1XetHO7CDdB37dTLHqc6RqRDJQ8VgibHP9/eoiVsZCrPtv6fSO8z26jrxzVuPhT54wjE3TeHzcnCnR23YvcjSfdVj1E9Of5pRyXVVlQVmL5xIu11UOrR+F45XYlbfPGJEfL5Tam42Rwz3d9vfk05hrhSsVSDfNVipr5mYAosIXWCXFktM45cYIqs+NhvITHbsk/aE2b8LjS7za9A0lJhvt34IKS/vsoM0nO8kw6S6SYP0GmHCKhRrMLzgRw9PKX1guHnRzqukPRcD4ydZ6ZqR7qLTNgDGIqiFpg6k0+QC1utq/oIlI9NAmzsqVTXZJamyR15MrGj5klQE/U8+VZs/r2Bqk/Csw5sAS59l9j8Pqf+0cmrAwtN3GnpueDlXCS4C3iTikuJeioUPUvk25dlxWPe4TA3Ni8NUwhsYfbkeNQm55BrzY+vd2I+KYAaDs1TCKF/AUtqpRJIeD/BiUmOPElFnqq9sS1MPrbXo7xCA4eZu/pwRtjQF7H7wJx8jHk/OtP0nmo1wP6U5ggJGy1b/T7NtJc+4s8+4VoG+ApI3gxewxpC+8j9gKC7Wc99Z6XTAKGD3b8JMVB0iFC3/uarAD9AL0aEP1I+pivto/dBjCLYNNojU1f8CCjFO5uwxndyOtv2B/tXVV1aBPQDMHcAaGJfISu7SQbtky5mCUJAMc5+eswWGmZXpsfPRQJDBPvPzPlInw1gt6wfz8KRFHIPK/0QYP4LugYvdM1odOXj8dEY51uZ2janxAI/xRb7CzONGSPw5o1izzBnupOSxvBmXbch8LOxkV80tuCsFlZ1vtVjiI4dFnrmpOaUaLEPn2klybup6KzLe4P82/LltrvQ8zQyJyTPG0YZuKVUjjx2aiLtfDO/aN9sAoeCRlsrBIliWT/g7ymdoHnyxz5z5uCIq8+W3ksXVYR4jX8aJ0ZShi85XDAjjOPxhqg4YtCac5+TqS/OEvSxeWmGFO6CA7MdGIZhES4hs+FwqEiqU1ReUooqF2ODHoun8q8vvWC8Pyv5Ix7mkBUCcUKed4viQDrTj81PRA0n6UL11MtqVD5kAUZINfJ5gWIlWnFE8VkfJbMbnvM3bqR1etsDrqZI3uDU0wRl3J5uHKi5cvWAWEBZkQEAJTk4SGx+VCxRLI41rQkWyhk4wPDIaVEK+sRYcQpaSBtt9nboFgcMgYaejITV21LthbJ7bo87rThN0fY3BwwT5lwCdEmr1AX2wlIBAahkaaFEAcMDNm40yPlaF8P8wwfhu1fu0br2oLWcsKydq4q8TajQgsasVHkwkCBExrh3LQTHZwZJ114tBZADohCYMUZaqryrNwUXMQbfhApsTSMjTapOqAjraNgNoqVes/GdkrcMzi3jURFy9V02KTGiHYoBrf3PUoYqyCicNQZgrdajMxRyZStPu82BcnCmqtBo3Y6yauMpu1Lyrn9DMx0TW56HF+7lrsK6SUsZwcVX0ovqJJx+maBmOs/ahAg4zOYHjasTUszCeI5UOjwtxBsyc7wWwqktvcFodGCWjkmwy3njTp0kaEmg1gEUk8I46WGCQJMC8vFloGBONw7dHGZU+d4HL5nrUWXI1JKbCEPzybtbcIbp/zAmdP9YqFDfWHJXlZBoHx6jkTyzolgp+E4iQtOaoBCEQONw4Ammw3+83sQedIvNfjuYw6Bxsv90MmI0CVYbEvGGtZDzRbuGdL9rumPYPL0y1M4yUtXGxYRCdRCQoFa9pLYaml0sJwMUj+XHO1y+rsDWHnnz6dCEZAAUkMhWFtzii+QwcAnJVuJWrEqd6esBz//lzgW5MzbPCER3eUSk7IgxLlkes/zCiI401nzILOeJubCyl0jx24l/o+BkZy0iIn3P8KA7kxy6lkYX9RpkpzjGevqq/uEHBP5Io7ouiiN8HDgHNryJ8NwT+vjUPfMFCCFGlkFSkS3lJtEP+Si+PFlVjLMvOPQDQ0uTjwiiD11IkTnayS6iPyZjuxJJ/3PRhSth7smcT1uPAxYAc7A9AX+Hle/qrZcn3kB05THwtuMsrvnSA98TNbPiVVKKjZstCMafOlnti/buLfyAIomzFJB4QBGZA3gMewsa1refbCAShmAB/FlynTEn/xjIeqr6UFUpJY25QSEFL67QvhHpU6mnxM5D74a25ow4ybGe4K1DYzBM1nOpGDDEoGZHNGeD2DHW1+oHgWxzUay4I5/8cOFpJAtpWogxGDKkRPrr0GPz1L1DaJ4tAGZN6RDH6UtH5JPCyGLhqMSrRebutsEtmd1B2Jk1eABx0vlAeEKPdHPAkyuW03fF2L8LzubxPeomHr1LRXuQMJNEb5h90JGiXHqJ/ZupoalImvymA1ECxsjhY3QWnkkJm83INIXP1WyrYzjZqbPPmtwPSk60Mm3e37yZ3mzMyuFz5f33eyR4o4ti5dXaoT3Lg24D7GsYWVmL0tiiSQo92rq8qVjj8KaXSUxsE9b9dmlR5OdvnSM9KWNrcfLfbN8tLy2qDdZ6N6sFWnctBKs37m7+7VDu7shgvOk/iV9nmKu3de+rq0ElDoOIPUqjZDxKsuNFSe+nOn5QP4gAAVADVCy/I+g9Ct+c/sPvQWITf7qEcax9LBwotm3vXiMqufmwYAMNEmlTeefArCL8mLkxjQsmzVn/SJi1ekTLQvEDv0Bgmjc4X+T8Ap46BsOGFGU6643UtFvEM6iVgVBBxP7OJlfsu//WYw6W12mvOL8HQztD7GbpbpefGWn6xq47Pu76ZnzyDNmYRp3FJOo71ZwfjWqoMbZNwHbyQvu1W94W786jbJYHy5Fyh0JO6C3puVYQqHx38WGHM9tQVWSYNPmadzHLpuYqkQxYuhN87NGziuHcUjI8Rzq7WWXMw1BjQdoZQVNa8pJA32IIKL5lIVz+QDc9CV5hRDK+7sSfeil5+XK/OT6Xqyqbb3FrPXRaHqrszla6lML2U3k4SyeKW6vcSLOriYg/qj0g6hb5+giCQ4gAVaKjYnigLgHPHqDektHIu7f0Q2wMC1LsmfmO5YCYKLF/jgRlnhk5KMDKpE/IBcI6qF00ETDFwaNyAXpEibO+EWlRBH2/eThhFQFX99nnKB2h6L+vBO/eF3V/1mKSeTLOq8u/s8VlcT0vfzBQJ+2Tfm6O5cv2AhNC8s0LtQY7XyFNcVWtbsfbFWKMxtp2ihyNliG4cdu6HmTckq/2feB4J+TW59emZWlnseqfh09hEVaJD09NZhWzGB5qogqnEYniiTTsz+3b09ybqPP5TgJ0Z+mqAZIJsN6ktFVL4NIXQ17ScyRwc9WQ5wlOm2RrFtiQpjnzOZ0u6bPIQ7ysg+TqR7VAwGjUVuFpf8UnTUMJehXAp2SiRipI9nBYvyLYxPHdc5NBvHmHPHcwtjl1Bis9D2zjnNxLRxYR3YaaKPEQDTSI1Y8nA40fB+MbDUgStb0FXD51SFphBnZeGiGEPC0O1+1/0tg0dHKrSuWEN0AES2OA9PyAQL4G4E29WPCtn8BxS9VFbbPwDdBkeSvMrM8WOP80b23se02Cu9jKOkTv7i5Dro1jmJr8BWy6U6uQm8sAwL+2aLJ96MbbvPv4nZDArUK9ltSBy6uiOhr/l7j3aeB8eTANk7DHhP0h/iucQizS06amxLOrTVSFzk2+AOO6pT1b/11fuh1rLciSn+rO+KcnKFK5nJPDaKHzISUlI/eDCen+nTo4TahHsNsKVJXVGpE+zZpAIVJ1AH2VGUxdgGZJRmDwz2ifCoRGLaLyq1eMeO4lgHbL8yO8NrdNx5DIUX3miel6kV7en3Jx64IS3WNsbfscO1eUmmYrpdjA8PeD5SKn7/fz7rI/hD8UafUduzqP3T4OYV1ZscgpftoHSkwTsEDp11VtYcbRsOVFE8y+nt57dmLwY0C916OrAdDTt514oVtaI6Yt7Xdmid8zjxWJeGInKQfDW7wZsW/xalz1sR1Pl2t
*/