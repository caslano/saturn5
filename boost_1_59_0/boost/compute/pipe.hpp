//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_PIPE_HPP
#define BOOST_COMPUTE_PIPE_HPP

#include <boost/compute/cl.hpp>
#include <boost/compute/context.hpp>
#include <boost/compute/memory_object.hpp>
#include <boost/compute/exception/opencl_error.hpp>
#include <boost/compute/detail/get_object_info.hpp>

// pipe objects require opencl 2.0
#if defined(BOOST_COMPUTE_CL_VERSION_2_0) || defined(BOOST_COMPUTE_DOXYGEN_INVOKED)

namespace boost {
namespace compute {

/// \class pipe
/// \brief A FIFO data pipe
///
/// \opencl_version_warning{2,0}
///
/// \see memory_object
class pipe : public memory_object
{
public:
    /// Creates a null pipe object.
    pipe()
        : memory_object()
    {
    }

    /// Creates a pipe object for \p mem. If \p retain is \c true, the
    /// reference count for \p mem will be incremented.
    explicit pipe(cl_mem mem, bool retain = true)
        : memory_object(mem, retain)
    {
    }

    /// Creates a new pipe in \p context.
    pipe(const context &context,
         uint_ pipe_packet_size,
         uint_ pipe_max_packets,
         cl_mem_flags flags = read_write,
         const cl_pipe_properties *properties = 0)
    {
        cl_int error = 0;
        m_mem = clCreatePipe(context,
                             flags,
                             pipe_packet_size,
                             pipe_max_packets,
                             properties,
                             &error);
        if(!m_mem){
            BOOST_THROW_EXCEPTION(opencl_error(error));
        }
    }

    /// Creates a new pipe object as a copy of \p other.
    pipe(const pipe &other)
        : memory_object(other)
    {
    }

    /// Copies the pipe object from \p other to \c *this.
    pipe& operator=(const pipe &other)
    {
        if(this != &other){
            memory_object::operator=(other);
        }

        return *this;
    }

    #ifndef BOOST_COMPUTE_NO_RVALUE_REFERENCES
    /// Move-constructs a new pipe object from \p other.
    pipe(pipe&& other) BOOST_NOEXCEPT
        : memory_object(std::move(other))
    {
    }

    /// Move-assigns the pipe from \p other to \c *this.
    pipe& operator=(pipe&& other) BOOST_NOEXCEPT
    {
        memory_object::operator=(std::move(other));

        return *this;
    }
    #endif // BOOST_COMPUTE_NO_RVALUE_REFERENCES

    /// Destroys the pipe object.
    ~pipe()
    {
    }

    /// Returns the packet size.
    uint_ packet_size() const
    {
        return get_info<uint_>(CL_PIPE_PACKET_SIZE);
    }

    /// Returns the max number of packets.
    uint_ max_packets() const
    {
        return get_info<uint_>(CL_PIPE_MAX_PACKETS);
    }

    /// Returns information about the pipe.
    ///
    /// \see_opencl2_ref{clGetPipeInfo}
    template<class T>
    T get_info(cl_pipe_info info) const
    {
        return detail::get_object_info<T>(clGetPipeInfo, m_mem, info);
    }

    /// \overload
    template<int Enum>
    typename detail::get_object_info_type<pipe, Enum>::type get_info() const;
};

/// \internal_ define get_info() specializations for pipe
BOOST_COMPUTE_DETAIL_DEFINE_GET_INFO_SPECIALIZATIONS(pipe,
    ((cl_uint, CL_PIPE_PACKET_SIZE))
    ((cl_uint, CL_PIPE_MAX_PACKETS))
)

namespace detail {

// set_kernel_arg specialization for pipe
template<>
struct set_kernel_arg<pipe>
{
    void operator()(kernel &kernel_, size_t index, const pipe &pipe_)
    {
        kernel_.set_arg(index, pipe_.get());
    }
};

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_CL_VERSION_2_0

#endif // BOOST_COMPUTE_PIPE_HPP

/* pipe.hpp
1eiNS8onpa0Wl5fROoYuidTVnzAnOigf72K1qj9+jh1GYqO6zypRSQonda2EEWgG3HBXRqsOrY9tmexmtgC0W4cUuJQ6tH6mWoNIdsTlsrJHecnr9czcMMooc8bzyrQRt+5j4XNEe8LoREFfQLtisOSOm0zQFe3VWBL24AxzVc1a3n3o4sZfPL9wR6wDwXYDv80oNwi/cHeUrVZBZmp4qQPy6ZjTpkg/qPIbfh7TzkA6HyECQteGeUcdmpZUnLvHiY1PtOzoaA1YDzDZ7zlhF5FqTnJkSc7CLjdP8jtvrqYa5yoKOlS/4pdJboqdE13m25O29GzmZehTOxOXs9fFL765C0ucf7acPvGkLvbtMJyJ4SK/vtHt7IiB8sqLofoEXZbP8xkgnFka7+VFqOHgEkXHxoR2f+esBiwF/FDenBi1FGxwP+EsxmpPWMwHJkBUHgxAMQkYgORjbGP1SmyjDQLwrh0osN8FGLDfn+cSJ5iShTtd3RW/9xMnrWahkRIqmpZKk1a5soQ8MPjYDRMbALDctCw3RMDV50SlYRLacHnApr7JJ62By42Sz+BGOkPgYQ+2JueVdd3aejiWv2fG1M0p+fMYMIIboSmrKx0UNp6Kz3+eYaZMMMtTeiIlWNs59An4IaAqbn0xDurNrjALkJ8fH2uDIgT6Ghaptim/FEzh4lKNuHVsDi8Sn+YVz+ElqQ/XtykHfJFSyBtum8LizRvfpO6TgSnXPEdRWchFx8Wot2n3IXMs6w59X66kj5sU3shsrUjZOVnW4Nw3eu6BdJvpThcTiEw6unG4aIvWCoGd31E6abuPC84YnVb98DQqXAa5HBAFl3O6vSbMP8VARbGi6E616vuRMte8a8gdeT35ZqTKvmB5MsGVFiISpuCdYVHlSE0V0DMcbc8c4tvVc8+AAKeqJD+9a8GnmJp2Lethwckgo8MlrPFYVVfA0NfRWHHbY+hWVJc1+cmtm8hhD/qTV289qB3sZC4OSbQjA9349ipPCLrsSPL1eoXmKJv5zau1juO5zZFTdgXniVyaS9yIIsQdYgAJtMaTBOt4D4p4Bk72NxhyxZrJ6rWgfYSQ6csPLdMPehDL3MeTQF0YrTh+igaV4AmYb65gmxGFQnnH8dFA2iTLMrPdRYGC/CpGirunps3oad4AqbQqVHsr0CUwKVt64dA2uF1to0uxiNmeWRS2PCqdGpi0h5kkLHJorH2deoufuaoaS+x4crlhBtl9UQO5GTiUwX2swM2aKpbc2ZBb3I7uFic9N7zpEy9fStawOwiwaohe/jpgSPJRrTqalb59GfnFjTid0quRXgHsSqnsJeKO+iEJk1WHqJZ6auxPtdLviX/fZdhLxlPDCZpofRRtnI+g5VJUmeUsmg2jVpL0F1WSGsLC7TkW6yjSuhZu0nLLc++Rr7faTZvTRpODOXAfCFw9CA2NOFc0d7nQf/GHV6vPncCQmv2dBpuH6TdLsafEnFDTSyNWBm4qXf23TMW5wT0sgB+8dugQyXDTVctuRdNCQ38DMx7UauweS/vdvpi0LcFQFasTQ5pTFMctzGfgpahfm5rGBfV8fDJahMRkfAVsOEXu1Wg9PWLdBTr8kJkiJOjAMsEQYZyKvbP9ooTugw24hN+Gbe4oV6363j6rXt617wDJXtZvPnwhM6LPCbdgnxYz4IRdfECPE3rG/vkTNvADjFgLhhKt/r9/vmAqp3jWA34btJ2EW0iZJ54IogCaFAeUJ4SCgnImFl/uJBdHWIoCKxKBjyMib5FE2CWGaB7ghCAnDCrC6TH0FNPx0bOyld7hOoLubp9zkn7CwXQidZyUPvN5z6OEXbxPjxrqK4L991PQ9jN3r/bx5VHnmM/b+UrTg26l5RLMNRbcF+5GW9v3x97rnItEoxAQviU4q+gDKM7o+nhbgvXP8Z+bYOUkKu5pZztnXmedk5Op0rtrTUQ99pc2Q/CBYNqnMx/ZO2UFBSBbtpohUGlwM16XmngDUxRxfYq80ZmstKy06ybm5+Ka9sRywsMT6gUWecSbugR3LiuWtr4JqSowyerpHm8qu+dvM8EWwcuogAKpb4odwUJrigvJRpW6xy7E06bX4GrKJrc/8+IRTUGXchmytVKWNkWaDSniY30kWDVfkfV/GKwD1ZtEHkKLKg3McE9sScwktUzx7KOj3EKtrNRQsxw+aBpS5YU/oXffX2Z1FhMWVcoRprKDaon1JA/3UguwogwMnuv6UreiShy062mHh5Iby1nkjbbExQbal5fzUj8q/7pRgN41GMJ8NIBHVgZPSWikT81IqYmc/a3i/6BSpv20L2O72YA8K7rJklvvA0iZUcd7fHzs3YdozRWaudFksEzczB7d/nEm7970fu9pwSOF4ZUV2fOFCdb/IYSiIqQ/R4DQQSwL+zuwe47ADCjS++9WjRwqdiRfj4s8apDQjt4ZCA1uAN9OLQDpL2SssoJoX50E++aK+JMvRDAVIL+HKUDcHgfA6OEbTrB0T0EtDcBoNgjAfRYAgLvrF3c/oEi03esH+WcqItzwOO6+GKvyZGsRaoHipcZm+6HNXgu/uKtYHfLL3AoVzCSmNWH2o6hD1DMsBFiY1/a2FjRz6WdVFkaDWzy1X2W54Ywp8MdbSVaKSSCGg81yeuQFWmf51e8ZO4KV27HM4EEAje6iXVGo22p+3MTqGXC0+VUAFSuHIHyAUwsHLFa3ji7O2giL1d1VjP0iXEBYA/olcVrxikF+/abaTjknn7zxbl2jSxZmVBTEeY1HtWRLeGsjt0hfEUyMy22euq5qr/mwA3w0XE+7H3nJ9O/uS8tL5+mmiabaMdalEESNQlhYKpOCnLjnBIDiiPIB608cFySOTfUOVETqRnEA+bDrRfU91IRKj/3tYmnxHtVjNEOokw314Qn/YDgZodoW2yM/mc2fTxU5LZL+LWbNKIB+nNy61SnrWprbC+fOMUIipIaxwiSkjhKJ7tDA5q2Wz5blXOgYEO/nbaTpdSXIWl6qm5qdY8f+YqPHbSrNtjeXiYAS9JlkGqjT9SGpEqpgtArZtOVuhs4fpeJAoSpihvPLa+orB4PxNtH04WXOEY56lBo6qEsUlA2p/kQuFfZjdfqx0X4L3LKWLAJVlpo5NtfGipPWlIznV+0mTp1ykh0nUWlHyjDFpDwyffp/Hop1LnW5QiQ0X/px0X1uQ4Ok5HrchafYF/uZ9hnR0RHQ5XlvjcyWdZjol0HZgZrVZ9SyOSE4OpB4C/XVKim+DVzfaru91wzN8XIXFaI0BZlZxS+dZ9tQTXU7LFHoLMizEdu2S4SF+2qpTq42VOv5o1t4i9SXd7NvjdSLJ41aQpPtK5dWEcpE0hKia09CwobGW6agkCsv4GQc5KW8AgXvEzzMmMd4z1PoC0ob0ZiFx2KntBLQf13e44a0mmrUn67aiWr4kN521RpDy7FjKTKpA0orK4hXNw36ZZJoWzVMFsrcEatwG8jq2bcY8pXze7ppdhPVTaT2xZP8Vnq9H0UG2kl6JoijeIhwnsPTChJ+wK+o0tqqplbGQ0xWLkwkZGvQ130hvXcwdHA3yDxrhyHsFLeN7ZZ/lo/SDSSO22fPT0XlIbvE9K9kXBCZMHr0wWiWvRXBr2jUrm0yai666q8RRhS2o+GSBMOChfkcxyfQ4D6YB6H3Hyws5VdkzXKBnI/lmeFAq/D2cVteJtdM+PTwFaWL9ClhFc3TJAaUsIrn6ZNDypil/tPq8UXBR4zT5TIISIk5Fi2no4mL/waH9a34c9z+t6dgIIRYJC35A5j+mAwQmdGRbVTy0xOYmfp6s5GIZR2EFjJ086ErbwazZf10qBxgXN3Xe7NEaq9MxVNRIA7vrH5u2WF7ujCn83kkR2lhsA17cbq846As865tUog4Hn584TunknNzqK2critT1URAXKGZ87vqpqb7Ko7Ho4NvWD/RnutYdgt7Wp9wpWxL6no7L8n4oSEok9pF2XhItliXb/hHf6yQVEODkXmTUSX/wRcXa3HuAiWRVn+rQhH+WDPoEDfVBqUoyhkSz19PzOGQIgZR9WPLNWpDW0/f/a278ofDzkteJy2f59WN4FRWO5fgL0QU6suNwAbIeL87DHOawYZwSkHszdL54IPdciSVhVIkidmjUfh8InHNEcqMVVEWPGlpw+G5hNlGcw1RN4BZddD9ObElSSOZD/tDeneqb6rWDOJ331pSmc1OLFleHU82UlqjWSiW+7DTKx66NJrHQVFXVw0q7NEYRpcnnX258I3Y9Gnasl6bFwoVKzUqOTbqPI85/GztOLkITs0RducJ7FNbvPeua9VhZQA+tVOh+TotK0nZeFvoRuKNRX175JJCeLFNKEe/P0vLJe0pcy+0m8s/6gbk2o5n/nv+szuYXfyuyXgpC457ProZiThf2Zw99lakGL/+PMgICAx/AFGiOnZm3OIw+QCqfcTZbGJokd8DW3ApkR09BBrwUK8+CAQcdJ9Ptl+vvq6vn69YzgUAvwc8QJw+CoDR/RftDNrO0RokwOE2GIB79/XAxd2DgxFzEOWMr2LOXoSvegx2zSVhMzJuVp4UJnDkPuzYH/qGTfRGlPwjz1vlXbe4Rn2LLKMp0H+roHV+a+YU5gt34kdW8BnWfXTapK9DIPbbwKZCcamrs1c1umKB5jOkqSBb40S6aGRsljllXuv6xKETD1IOCCt3ErwumSa8sxR5vdfJthZvqPwJ3p5F5hADVxMnVYrEhVmhUpedx/jEE5L32kwW8OA4ORGwY2sHHe20NVEeKE8w2e44eRzm0Z2Ge634Bp+DIS9NWetEX25EMyctYleQ8PzIU7G9iQ/c1xNkQgNdeKVaPI5Ze1OrnSw9Sh0eS1mejhvxn5mKhsbRrNsE6pjbSUHDgHWOCbIbIbyt2nsR/H4oAxM5ftyOiH36ncnqlZtnss7j/Vgo1nwa59Tc3OK2W3Mpqmee9v9U6eRr8M+qIzPkxnym8GeYoho6kiWXWfiIlddZXYtB1psKy4SxfbT4ul/dE0nojj8LTfe4Xp7QH2IqOrgoHI4ECoZjoe4AUdpIxhlKZlO6XxOfZqLNt8Vb964/ri/4UExkHM218ol0CjwbP41ntMrksR7zOqW9ZMcNFBoozDMdkTymlxPXtAWSau678Va86jAfiG4B5RSSAxxO2ixFZWHULOXXL+iySc0TIk2JBXEHbcJgT4nY8jDtXdljKHJdK5/ZqMvTXkHKsaDTHwy9m3hx6zuPoJgNZXqcfSLvgOWDb1QV5U/hUYO/5eRPa8Tz6CmDFSiSJPKUoIoUyJMFf/goUCSK5P5P0zdV0Nfazf/n4zb/1TcAfTB3D/Qt9xboB5EASogIRb81m8/nQE8CI6odCRBStf/gVk6EG7AiZvXNAlkCMnhAIP6cHQXOX6l/d5ac2t9vpKDODRvoHf02gP8LRmfVpxf6ShwgLgYNoNAVEABTHYA/pcj29R5Wx8UW0O+yCQA/9GNmFrQY4k3nGt38X0ldpIjeiV9HWAZ7QQ3P9wVp/+Bt05PlJSoYgFlCGPskIt5Di9DVOzF4XlhR2zqQ114RJxwETls1jxOea8stkSuXGeTnX7XD6OE8Z16oQ3XDxIbD6Fpg5WmFfM/CYQQY/Dspm3W7dGE/TnoMlZQBNup8ts+5zkcW4NHTeAud972x5iVl9IfKCKhEJCsvAXWbPCL1YiOXdF7+ZNtwKpp5LLYJ7IyRxlqN/i7TDsHDKdMiZrz8tgyD7XbHrYaFuqPsy+nnsqXxFwxddhqTkKCQs31ga5vtgTbYEqOIP9KIExaGTgTu71q403McLvxi3Olj+v3NIrP3u45bZ8I6WDyACVb0I2qNqPw5iKSv4q9WC0PENHIqOyBiPismRs+Y6b8PqtDx5k1zSzTeT85ZxknFHQd/LLcB42cMqI3faYwY+QKrO/+osFfcEF8CaWd6Qs1Chr3r7WFfcZuoLwaSavQJQdfTRYAqcOL93QDN87BYyOE4ZKWvMYJzgreZvxxz1Pfc8kyd+3LYfsDXLGNRjf3jLPkqR+QAKfqHAzBra9V9d6EtZ89/+A4MZn/dvga7XUtutC7nvSU2YS01p7uER77BY+pqLIlPHQbpxuXnIC8eeMxQ8Y+6bhrwkwRIkaLnMh2zK9IlGPkF3VGoQp0ZES6NtWvJhasQacRxq7KCzCpFXE0VzSq7WEevBPsJazsoePGraqPcIw6nKsjhmTZvezYs32fMVlAoLVFzgGN9mWn2/DIegYoxmjmxd+qKKubFUa9gApwMQSj2GWVNOoaMBe21OKNx2TwR2IiousrNEO5i4F+W5lQ4I9Nud/OVzQxTULF5QhVzceS+IflbacASdx1I6FVTeK8hB4tIl2bNioqrr5wkVaYPuP71Tgjk6He6rB22RLXZB2gnW0szQjNemtng2B5fGVJromub2kUULPQdu6KVtTbNMDeeTR7nyLgee4EFa++ef7YI2cG33Hu6Ul/8CiB0ENomFdjSpQEQqsXHknBz3vYWBI1ReSgtFO2lHrEQDcN6P6d2Gn9JpVlqyZH1nwOig06N58ANTo9JxEGrgknwknWsl9BF2rzLJcSZAg10wTy+HANi+vl4pFop9MiRZwo/CGUcArVHqAwFFn7MWb6e/5EI+wGa6uMfYprDFkdbk/EKcJeUprUKw7JEs2THRCXhRbclqr1fOlpcuY/5dCNTZJ+CnpEowqXg+/h2o7F9cZaESVV4V1vp3EZBMzVh9/nrjbjIjvyzOSB8CwsJUrrrKPeEBmrk9XJHGB0ZpGAPy0+LXqqmqUAIWy7RWivQnFtD6liwdCqcB9/k1aNzYQtg76tM6NJ68pl3oimWD9ynRHqZutHoxjrmdtBkzmCzJ+SC+wzL7V1GIdLrRcP+M4pto53Kp1a+eo5gToKlaC/B0b7SbelxfU6QJ/svSdPbAP2LGkZt6NRGn/rQrdboxZs5Y7UVem7/acpSnu1CEeWZtUlvhAaCW/IDDAQ2La13fLXqI4WSuJlnMAUOobaMx9bbNtrKYyChazlj4L7PldjWBw3JMqUTCXnVAk+J++Vv+urxietuEKCRCMbqO+PalC5hXRR4UevfFVRvwa89XndcK6IwPPm3yYE1qMwO7ud4+zLfkNajEyWy3P6GkYhwKwvigYbVVH6U+zc9DgXQnSdWjR5//SKnkNwiDIF7e6r1CzLhiW7up/hkLt8BxvQhcDTR3OxssN4w+LoK7nXL/fkisb+H/zgioD148RQ4LiK4ick359ecGnlQZjOJUXkdNB0rioc7a3ICJVtvi5PDFqXfxl45YXMjkV7A2zgUhQm4l9GVlEWZnjUv0Wkziree35D+crFzS9j29g+7/fNKA5CmM2+hG/WWm5byESJSK1iO7RzforRiNXL4voiX08G+AQZy39jJ8hRXYVo5lo/GhlV5mWZFKJihgGUyQPNF0srtbDnSCgFQxHOxQA3yHiK+aW9uxhAABCz708DmGM6K5xnKHhHQQm6BgWXRE7gwjZitO5IaUPbCfOjXtpU2H1z+vaA1xo+gMGEjWBdc1ii1NawUT0UILDmtAu3/rsWuBcYrGn+JshSF2oaPTBju55RNW6nN3Wz9/VI19sFcWn7ovuu3hgjm18SGQiG/ltskGNrS1tzE
*/