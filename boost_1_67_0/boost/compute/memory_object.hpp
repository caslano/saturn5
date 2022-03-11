//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_MEMORY_OBJECT_HPP
#define BOOST_COMPUTE_MEMORY_OBJECT_HPP

#include <boost/compute/config.hpp>
#include <boost/compute/context.hpp>
#include <boost/compute/kernel.hpp>
#include <boost/compute/detail/get_object_info.hpp>
#include <boost/compute/detail/assert_cl_success.hpp>

namespace boost {
namespace compute {

/// \class memory_object
/// \brief Base-class for memory objects.
///
/// The memory_object class is the base-class for memory objects on
/// compute devices.
///
/// \see buffer, vector
class memory_object
{
public:
    /// Flags for the creation of memory objects.
    enum mem_flags {
        read_write = CL_MEM_READ_WRITE,
        read_only = CL_MEM_READ_ONLY,
        write_only = CL_MEM_WRITE_ONLY,
        use_host_ptr = CL_MEM_USE_HOST_PTR,
        alloc_host_ptr = CL_MEM_ALLOC_HOST_PTR,
        copy_host_ptr = CL_MEM_COPY_HOST_PTR
        #ifdef BOOST_COMPUTE_CL_VERSION_1_2
        ,
        host_write_only = CL_MEM_HOST_WRITE_ONLY,
        host_read_only = CL_MEM_HOST_READ_ONLY,
        host_no_access = CL_MEM_HOST_NO_ACCESS
        #endif
    };

    /// Symbolic names for the OpenCL address spaces.
    enum address_space {
        global_memory,
        local_memory,
        private_memory,
        constant_memory
    };

    /// Returns the underlying OpenCL memory object.
    cl_mem& get() const
    {
        return const_cast<cl_mem &>(m_mem);
    }

    /// Returns the size of the memory object in bytes.
    size_t get_memory_size() const
    {
        return get_memory_info<size_t>(CL_MEM_SIZE);
    }

    /// Returns the type for the memory object.
    cl_mem_object_type get_memory_type() const
    {
        return get_memory_info<cl_mem_object_type>(CL_MEM_TYPE);
    }

    /// Returns the flags for the memory object.
    cl_mem_flags get_memory_flags() const
    {
        return get_memory_info<cl_mem_flags>(CL_MEM_FLAGS);
    }

    /// Returns the context for the memory object.
    context get_context() const
    {
        return context(get_memory_info<cl_context>(CL_MEM_CONTEXT));
    }

    /// Returns the host pointer associated with the memory object.
    void* get_host_ptr() const
    {
        return get_memory_info<void *>(CL_MEM_HOST_PTR);
    }

    /// Returns the reference count for the memory object.
    uint_ reference_count() const
    {
        return get_memory_info<uint_>(CL_MEM_REFERENCE_COUNT);
    }

    /// Returns information about the memory object.
    ///
    /// \see_opencl_ref{clGetMemObjectInfo}
    template<class T>
    T get_memory_info(cl_mem_info info) const
    {
        return detail::get_object_info<T>(clGetMemObjectInfo, m_mem, info);
    }

    #if defined(BOOST_COMPUTE_CL_VERSION_1_1) || defined(BOOST_COMPUTE_DOXYGEN_INVOKED)
    /// Registers a function to be called when the memory object is deleted
    /// and its resources freed.
    ///
    /// \see_opencl_ref{clSetMemObjectDestructorCallback}
    ///
    /// \opencl_version_warning{1,1}
    void set_destructor_callback(void (BOOST_COMPUTE_CL_CALLBACK *callback)(
                                     cl_mem memobj, void *user_data
                                 ),
                                 void *user_data = 0)
    {
        cl_int ret = clSetMemObjectDestructorCallback(m_mem, callback, user_data);
        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }
    }
    /// Registers a function to be called when the memory object is deleted
    /// and its resources freed.
    ///
    /// The function specified by \p callback must be invokable with zero
    /// arguments (e.g. \c callback()).
    ///
    /// \opencl_version_warning{1,1}
    template<class Function>
    void set_destructor_callback(Function callback)
    {
        set_destructor_callback(
            destructor_callback_invoker,
            new boost::function<void()>(callback)
        );
    }
    #endif // BOOST_COMPUTE_CL_VERSION_1_1

    /// Returns \c true if the memory object is the same as \p other.
    bool operator==(const memory_object &other) const
    {
        return m_mem == other.m_mem;
    }

    /// Returns \c true if the memory object is different from \p other.
    bool operator!=(const memory_object &other) const
    {
        return m_mem != other.m_mem;
    }

private:
    #ifdef BOOST_COMPUTE_CL_VERSION_1_1
    /// \internal_
    static void BOOST_COMPUTE_CL_CALLBACK
    destructor_callback_invoker(cl_mem, void *user_data)
    {
        boost::function<void()> *callback =
            static_cast<boost::function<void()> *>(user_data);

        (*callback)();

        delete callback;
    }
    #endif // BOOST_COMPUTE_CL_VERSION_1_1

protected:
    /// \internal_
    memory_object()
        : m_mem(0)
    {
    }

    /// \internal_
    explicit memory_object(cl_mem mem, bool retain = true)
        : m_mem(mem)
    {
        if(m_mem && retain){
            clRetainMemObject(m_mem);
        }
    }

    /// \internal_
    memory_object(const memory_object &other)
        : m_mem(other.m_mem)
    {
        if(m_mem){
            clRetainMemObject(m_mem);
        }
    }

    /// \internal_
    memory_object& operator=(const memory_object &other)
    {
        if(this != &other){
            if(m_mem){
                clReleaseMemObject(m_mem);
            }

            m_mem = other.m_mem;

            if(m_mem){
                clRetainMemObject(m_mem);
            }
        }

        return *this;
    }

    #ifndef BOOST_COMPUTE_NO_RVALUE_REFERENCES
    /// \internal_
    memory_object(memory_object&& other) BOOST_NOEXCEPT
        : m_mem(other.m_mem)
    {
        other.m_mem = 0;
    }

    /// \internal_
    memory_object& operator=(memory_object&& other) BOOST_NOEXCEPT
    {
        if(m_mem){
            clReleaseMemObject(m_mem);
        }

        m_mem = other.m_mem;
        other.m_mem = 0;

        return *this;
    }
    #endif // BOOST_COMPUTE_NO_RVALUE_REFERENCES

    /// \internal_
    ~memory_object()
    {
        if(m_mem){
            BOOST_COMPUTE_ASSERT_CL_SUCCESS(
                clReleaseMemObject(m_mem)
            );
        }
    }

protected:
    cl_mem m_mem;
};

namespace detail {

// set_kernel_arg specialization for memory_object
template<>
struct set_kernel_arg<memory_object>
{
    void operator()(kernel &kernel_, size_t index, const memory_object &mem)
    {
        kernel_.set_arg(index, mem.get());
    }
};

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_MEMORY_OBJECT_HPP

/* memory_object.hpp
XQJTDO1JuYC/izaL+Y/ndEq1GUv8u3HHEKxr2poiTe2nw3BZbYE1tnSWcxebt6JWTQy06pFRPIA6CMKeAClR3TeLB9DTSYdHlq4Y0LGxktmi7XGwdTnGBrLXMV8shARYF6oAOW3eTLH2UfpEhYmtyXDN2AqIAL19Y4qaSSOZCaIsLib0qZP2puHRTpR1aBy3v4KCzjbs4OgCk5pSVI7CdMNNBHkyAGC5C0BPwSOh8hAsyMXJKBcnvk7uSZ35u8nh8LQKeO9AftVTN79EbkjoD65SP0SKyDM3lSi3cxeAXtLieKYx+xD0996fDAwz8A4zpceQi2IM7cz2CB0mKwguPA7S49gUohPMo/XU6YAcj4Jcg+rdeF676iU8OuBLKtBTq+G1qXhB/b/QwcLq0cGSddq1E3UoWk5D0kWu+0YBY+m+f2vuVjGwekDnM5YCbfPR0/KeBxM/9OM5vWpPcZpOteOL8jhpXLeKmaUDemQbD2Bu9n7JOb4xsK60A08oImLFQE3yKL3F3Vu5UpOHeUzpBlmpp97/Inq+w3j+T1cFVYqALV8v7l2NZGknXwiiUi/y/ZgS1tUG/V0gu9IB5P12AAAs/9OsEmZIvnDXk6f691C6dxHu1KASW1CApdQeoBS+NuipqOUyf5/L3126CljX5e8p/Ymu9utqH2VvfRGPw9t1HvWNzvbb1ZtgiCLXgAbyahqYWzOiS0AHV20FIuW0Duq9jq8bvtD17KgPNOohMIeBNXWlH2Z/ttKz9gUYKjyM05etdK99Qlc7qC/xLhgExl7AOgodYURU6s77a2PujFZxEN5BARHsNeKLoip0pV0+GkbaBilZx2gpUyeiIbS3AiePPxSIWksTXcum+KzZTWpqVkj8+DXarNXWV5rkYcZogbj2FdAyrnQ9T1ySiAHQHYEZU95Ic9pKP9Pc1aJz1YDuJb86MokHk/atAfYILqJNhDR999dxSLW4AvCNcB7ESFI+o45GvIEH76IYhDqp2Wc3Ec/U6O8xpT5iYYX1rsJ63x7cyrh7FY57jfSKGS2Xi7lr0JvVwN11xelZR265hy08fKfXy5RW5m53bG/VlDKPV1OaAWZFi9KcgeojW3iEFR5l7g4Zp8oK5T5BGUwXJLkbjEGgTpqu1hMi0Ep54aC4CxrqvQ57CKAQvXVQaGqsEFdD+g1yzNgV6LWkOpPWxEarWqQjovt7n4ApjRYYGDDuEFqEZIcB5aWR5UVoah0wBL5WSP7EYfyFppRDhzeLmVdYQBqEcA9qyHrj7oZi3evRVzmZhj45IAfTaJusz8m2kMduC23KxR10MLk214prMi0meKEg4/OXA2AaFtCnldAQcKbsEPv/id5BjEIIodko2eHRpBerIT9iK87xiP1QnSlVrDDkKmwovQnETGFdaUa+DoTBfuBEylZ2+EDAVcUTcVrkZqt1azt0YD0llK00rN2vq+uIwjHSZp3O7d0GVCvCIyT19yB/Z9TRxQ9uGzBn1mmWM4nNs0up5lsQY9V5moaLtsj0DegkyAyekakXPYwMGz0vGXakSLtUbkhRueKHcY6Jm+rkObAgSmSDd2nvlQdNFOtEPG3IPt9FHn0XbmcBlwRXwJ/IKLYL/7ro6avWtGkI+6kS3Hm7TQauxnla5j2AQli2QJHXQ8ydnz/E3EGM7fTkE3/vmo6xGMNYXCUWV8ND7vFdk2ibu5qwx2mXvR8kJyEVQ1g2T6Lml4BC70mkkISNvcmQlSaMrKTvuosAI/dH9hAj5+cbmbuW0hN7gmkEiJia59hbaAv9cSJa6Si5C49agiO4CnfoaLfTU7wgBl4Oj6MMxQxI4MehnBsJpJQBSlcPw3zXQ8a0k2P48kM0827EoaPZ4diuSfc1xVC0OTYyaO4YNa/dbw6PrUZdews249g9TgtORjS0YLr8g8EvHsfuXJ3MWsfu+WZ68YhjV1pMgb7JXSQGwfDOiL+lx9/SOj9F+7yLYKJx3kXwUCO/H+aPR/zoMosJYCZIYoCV7dje+Oxf0UI9cxbTy3PNMvBA+icuzB0Vy3SOzNSJlQL7reW557jc+d9Ou/QuynBUjMcwgMcpDGAa9VNDDMU7l4JMIC3tAnlDYRjFyBrYHtPS45zKdqXRcwKlT5QyCOVOmiF3CHKtuO1aED30TtJn3aUx6aPvyiCWmW7w1ghOG742EgvD9Kdpl9t77kuQERR09CzKCOsOOivNR4EVxyhYAA/h4Hr5ix0ySvtyZCi58Uw+pHfo4GEoclwGFDGl7NkzwGh7lsFHOpcB5O51TNnsCGoUi1eFzHkD1vO1AkP+OV1t5MoO+PobhhWW/oopm7iymX/Q+FEC1Ar415lKb+Ut3L/p2cx9GBynrHvbX8kwHKOSv6fdduVgMFR6CVMquJlfzxLYdYF91kCvVXdXqP8GJm/sTrBEdXe5epjLIIzCTRjvuLUXyaXJqJwf/hLElV4AimZcnFD6t0EI8huyz/guzpdzUU+V628FrLH+Cpe/Qk3LOi3nDFV40Edz5jDOGYXCJ+tRC52KYpzPQLmNfoByoBEGeGPXHBtxK49TcIbsH3ROfrLCTdpSCwCqhA56ZdyBjrHJmwxkQPfZLEWlN5biGVEgxgbqZm88Rdk0T6fprO7Ugcrwv7A8W1m3llu2YKO6uwwQdJBkxvVkWLdxRcFpRx4XfZVHI9XDI/Z+SUySsKxJW48KU2AaHgRY5fGIGsiROtJQWiWkof+naRjTPfknGemWxFW73B2LMV30T/9LpgOaIac9e+a8wXpO5LjHjw9x3I3EcQfu4e4/35OtYRF1r+S712QMruO1Rsd2pfLZwIkkbUJC4znL6SaLb3RjJEGbsMWKzi7RcOsAhb4uhvZKV/M9UmfYzFtg5OYDVzi2fy6H7m0/vJ+DYSbO32TZj9G6SgWM41RgXC+OkFopulcnm7xywMRR+V4Jn6IV3oFNv1u4OdA8EVn3IPCxpUVHWGXqdqx6L2CyuPf983EWXnMvsPCx4fqlTF/+wACdz/VdXDCShctRTSx3FZZfwMLbHyAWfpzCSTdnH3Bs3IIMSszL9xOLVkD3QPHjlyNbS4UJEIQuarMn6zR7safLQNcDdUatLM2BTsUm0DvQWcmz8RTPsOw4x26Kp4CmU7l2D/Cq7oaZu079IycOMatlOjWtBnS1/EI+zRzi0wUxPuVfz6cLPOKBC/kU0grjfIpnXevfQz795A/JIOmtckWzyz99tNSDxDwpnCCMtWCKTD91nv7M1inbLj5Ps5i66BP12HAt1uvagoK+i6qEaxFu15bplIK1w7V2SpmCvBmsMMc5eYSh4ChbYyXn7p9hYb8fL+VRdmQdw5Cen1gptt2x3V2dRev1HRikfn/CtGVmR9nVGBS0ez5ocyskvvfKP7cZ6/R5Y50eZyzTUwh9zA0HEenYzmPimtTOxs5P8QN9T7hD935nY+Tyzk872+T2YeIjdkzqbOt8s7MtYsW/XdRaOIg9M/YYfY6Od2TpUV0dnfsiY2N7j1b4bOwiLMNBJI4shxWOxioc63o/Mr4r3PlmDIa16xg6zIx91y1IdZkxuut9CSuS0PlmoC+ts40UC1QpQJm4KhVWU/Tal48CXaB8vl6eex5MbpAK1XNAC8iOOirewEsEky1ASBmeavnZV+YdpX/yC9SUj57/GtPOUfY3DCYjrpRrN95u55HRZGgibcKpuclVuMlRVokltTBOxmAHPPOMYjB/mbsi5gAoA5vKSWJfguhdjKcgaekVdxfFAtVGqMuUd8svKJxP37VItkxaEMC6dBgsirBDxaH3NEaKGuaWzIT1QS3HL6ov9dMLNsgYqaOscDNIGsfGn1Ecc6WrsMKxcT7GZZPAi9UncULyPJtqOcouQ6bXUP/O0zQ0IuAPakh5HvFSKjLkhP9XDInA/08MOen/IUNO+p8Y8umLLSYXUcQ33jOSWNI3AtpQZTYsPBWvos+L1vNsDO39DX6Skhkb3OFDunu4q6RMujkKGDGkuOfX5/TH9qMszGdXikXwxa6Q7IKm+VM/j9kIxOWPw6dY8LJco7+63ei74cKNxqu50sdyPVzpLzbxgyx3gXH8X6ifYjAMPyjuhZdlbU29L3xo7DDwH9HtabY8cd+PMbZoNbeJ3ZFhd1jQJg7uSojvfTi0iXNrzlfCxGCKTOCKHQNJ4DWFtnOcgZX9psDKU3gBCV6ngo7fhVGxpVfXhzl1547YYfPyQjsYiTiTMaBMc9cP76Oj7AWcAf52k6PsGbnv9maa4/EnkKJ4t5TIoVPkDYGVfSZsnPdzC1PClpbFfJ6VKT0YTIb+TubuhlfLQQ9e3QNWqf8UU6PMLfRU28vjnY7XlDcbhcWxPcoPPYYB/OseTvxRoG1wli+p2Hpn5tuWAfTlhxxVjXnc3eEpoHttdLVd9JNX3bgp6eer5e5bcUr9fTNhgdvykvTKuvbGfZ14KZj0Dccdw7Nrxjtd/hTfJbiS+We5iH9UuuPnz31yffNnuvYiD6lXiX1Hz+mu1ff7LnXNcL6B4RauGXb8m0zD7YcK/NfkZyudkP2e7yLcWCB3Wym621pUULRTuJLCNyJGLDcjKzR0U9Iv3SBkc2cajmLcn4OVr8WxqSn7A98Jbf1m6RT/at7+rJBrL7rEHZsAkO817IwN0eb71ibwRn45CuXY1v47GDbZxubYshvVCa6xSAlH2UfoWRlyk/e+A9+u+dN9N/PcBXnF5kAoAe9jk5EEeuo2CQ79/yxJfydws4nNsfqseBNMgfji6XN6gAhsirzM3fZgW+k4rmAUcJJWehdzRMYAHHxLAtiIJNRVEwMHcCfgeRS2oK7wQ6Bbiz8coVPRyYFzurziChYmPIhdhkuAUQgWKvE4lPOy3AmxxWD+TDHtpwPoWefzCeNAY0IeuntpedH2Ih3xMphPYK3LPgf01IGej1oL9FWzxYpiWP/aQN14ppGtp12IA6B5nI8dt+sWS4qku/WbvwMp4TQV2+uTxgCnZb2InIZBBqirVOzHmrlWh7YHF8VcIHggmg4w+dlA1Oa7KhB1+i4NRNN8Dkj2JQYOWSMXBw6lR8YGDqVFbIFDzoglcMgGwkYsNUPfvAWo9sFUkf393qhzOu27emGtMmTfYQx53S2diP14l8UoPpUCOsS/AWFYA2Nckw+zpk+MiX6po3gQc546h3tA2NSyc7FeCt4vQnj14X7cJxU/eNG4/gh3p2AylU50BFGJ9mrkHPaKBADCsrXnK+jrVKX8qqSvjyvx5CCajSxbXPkhnh3Ea2HEtpvwHhK8xEMkUyqGPItr66J61/od8NopWGlKZ4iVWrv+xUrTWOkk2gO3LTE2BddM4LmLup7fQbMIWHMpCN+sEMtdxEqX4tK0fFksylmlANqDAtc2GDmWO5Hf7mHzPfz2BWz+An77XWz+Xfz2FWz+Cv4kTUqamvz2FDY/hd9uZfOtuIc2x7Y8dvFpEYr4+vk47NNfoKu5TrteIwGDRJ4UeNSWtvY0BnaF4sF2sGB2RE5AgogljO3qQDZ65wW52MxZwJTuY0p3LL4sDOu5eKEKoC/HixSOKWGm9GG4lXgCEwF1ZRPGvLvcfb7Xso+X7nSp3aV/dqmbSn/vUvtKa/hyKyvszz7ue04jdQK1ttdGam0eWk1xrRbrwsmmrg1Iy7DbthgkLSV3vUDUVStB6jK1hqlbmTuMtHNXBM6Z1VTAIruxdNyzZ84ytYK5K4HzeIf+Gs1haku860RvcDXGyp4gH8Im7u6TjkuXWlE6xrG9gxW2MqUGhAIYq01MaWfurS417LOcKWwHGd/qEX8aZTHJLSLReSwZbVWo262O09VqQ5HbcB7VpXChrUWxJ0KzUn1Jgq9RiD+5kNiuufS8jZ5kY+8iVw6pE2yX9FmtoOdMeqJOg8cD8EihRiDUQelBFbujWADdxmyXlQrb6Gmnp5OeKfqQEyydnoNU3hQH261pBELCvDuKjr4t6MxqIb8gagBs1xSqOo20Uzuf4/Hkg+IjHWYeOreY+wFWWB2vQJ4W9J1D6QVYuk8j94iHLjhIg9JZbcW2O3nTsO38upswpPloMYgp3jR8n/+3kLF4MXf3M6VD4pl90LHxp6jEP0M+8KbGbgu6roLYUbArtjq2F9ZgiLY8U1q4lS2sA6Zhaj9wpWP9xVjTXWdx1zN3M3c3M/c27t4EMNfjYQxOTkemHGbuMjxaVXg03ysyH07G7XK+cJ1m3xdotjO1ipHb0XWdY/1nqK7M3meVmj5Td0jHJzdZlB0IIa1rptVSKLq2oJaQ79i+RbqBOixbcIzFodUI+zBBDbkmr1rJ1AY+12pxNzh2P4Mjwc1ds6wWBTpud2zfZ2nKfnfV9/lCO2ggmv1tx24newb1+pm6Yj9GGn5HW9jcdaljt4aVXW77g0d0JdTVwfECy1BAabBn2x583oANsC6jKO2OzNYuqzmsIY5hU1daIGS7Vf23rlQZnn93VUDZATUdj1+Bn4VHDfiBs1ZV6cpJC18WU+QtEQt8d12GiUuMSNLErhybTF5io3RnPN1ppDuhe9kHV90qI8g6PwWdssvaFIsURXMhdIG5ILI3A+Xc23QF/tsxMIq8sC7F/uC+rs6ujoBy2Ka7yxzBqWTp0Z5T4VauIZfoSr8ZB78/293nePwMXqvprjC7e7i70uwW5sJ6s1Knu8OOYAuej1ePCs80tOo6xNxpA3TzujHts0L5Hu32ReJ736Szlzg52JxFKEjnLAVBw+Z4UDefs4BvIAvuSRJLbAMdc1S68/khtgFlVMscWzqKquYTpLAfEq+fwGVCCvS9OKdAO5NTCOebdOfxqNiIN6nGHddsFznKH/4Hhgf1XjNg6PqP9d1mNZlGnuagG+cOsC09sNyKR96Gcaw9Ba94RDt9MdsTPocOc3EOZ3U/PJPTE0xnWkymBJMvpTFquxo9+SyI+WwP5mOe1eT7ZqwOwqJ7Oaj26PRr8IzdDbVROonXh22erQFRswvL8YN4LkvfhTX1XZjpEd+aR3dvj65PnGla1/sXPMxUG0X8sCEz2ACZZro2+sRhJAPbg3Ae0/F+oYcuKRD/6NT1xWUh3xjeIn7cATwyGBlXAHIO211963moEdTVTNceTPBdyoP4l0/2gDDFEqEHQb4HT6uf1I8zJa3rxctdDUQPFIjfYINzrHir8Aw8erUqM0BgTMYFGhfA8sVg9V6Pc6UWe4cmXL42x8aISlw+bZzIEqAvK3+78V/O8k3B85gF7zadciHlS/xTERyEP/vLgjoNGeVlz7E+uFOjDI/+kBWJKuYhsjSWLholR/BTUgTtgdp2rBmoPYx/WPAo3dPlZMEOeNGCdQikAE9AtxO4Eqt4NwsvDvMl4lkb0MbwwuJ4x4+e/2rH1zwQ6/huzC0FybVHUHebsZu1/YT5MlugJanxPxa8H12So/S6AknsAq/IfRv4JdiArER5lmUpgWanTizF6Zmd61x7iO/qGcIajz1MlrjeicceFuqrbJrWTqyFNfRVKfoqJ15Z//lBrEQd1LRuxHl8B0w+YEWv8X19B9ai199ej/4epJb4G7waXf8q75Tdb3Q7K6TVbj1HoVYyJDO/eNjJrEBfCkzAv1abL3WK7373vF4WUpOI1SOzMchQHswARaIPD2WI+dfjAchBsqfd/dAzsNqnQFqknU5NHRSXDKKM6gd9+XIsOiwOMS8PD4Qwd7Q4QU+teQm0837ADi1QPOpPAY166taXxhuhPh7xux8n471TiEGxGfLSf0/b0Ae9r6Nd5kokkzXJK83VF++XN8tdXTxFnIaW8cBqMm8Vj0CXkEteMvITxWU3o/QchDxasMHgt3n0PJs8JiKegPLcHfWIY0sHYlYb76dm0A7k+5csi0ez5tF19vgbIadVm/iLB2/XtOtTw2g1qjbA2EMhSDDBbXiHHdYrgNQFGDWl2DEq2wu24yIs1BE8pjqzTmPXUze9RO1E3sLCS2vocJjHK15DbPsj4WJr/R7UtI/8Kn4J4rbNeMHlzBZlELU9ACVtmxxrVltQBpbK+z9/CNY0GXtGfLAFxMewIr4uEPPrDbMZPg8GSiea1Ikx9/q1ZWC4kGMdhCK9V9J7Kr6TDSOvOlzxjRSnOH5tzJpBNUuG5YrrjuqG6YMrR4t5AZacgDeaH6J7JZIm1OFvU7wOc42sH7yzcfoLUTLCQMJ+sWhAFzt/hRdBzqyPIg0OPm2cgV020YechE5v17IU3ykvXiX3i8WgxWFQbl+LIhC05m6lTdUfePGQWAepi1d5kR3qZWQXHQWWkV1JiyidvjrE2QIY3JEOXYzHCaM3tx+9uf0Y8T+WWLcdE+2YaAdzm+cviIewtKNOr9juyPNSXSOIpd9no5CosDw2YIsBMdx2Lblp5ED78+PD/XbVj+MlXR3sCurEsQLskOzcIXoX5YWDRq+F629Rw46tE39aJK31e5+Wt7914B7dd+1QKvIUbQxn6bwTDFoiZ6UFyEmeIl8SzG37SZDeMwb3on/kUnRAk3f2gkARMOIdQS8tVGhmiRsOJZvkfhCnUIHFxpVjtFMiavMGRm7Lktua5w/EokZafKmemEdUhpegPhsZxfbgXxc9HWWP4EF2j0Z6VYGH0QlskXAfyY97AnvwMH/ag2uGIidGBLb47i4evRiEpL/18z9KHPFefzISwbS6h5P39h7QwuH1+/L1CP7chKZ5yFONN76RC1fGmyCuRryJjCnJ0iNpse362UMOW+naJ402u8VRVouau4bWjaj0DBiFRnj0Ke/+hbE7DXRpBBlUuY3A+ObEwvlkG8NaxTRZYTYFE9x2AQipW0sfccQe226jkEFqmSJISqj1YV5nqir9xTRyd0CByCLyxRRAizuHfDESMg9UGKMaK+OJZVdQduX/lI0ZPMeDro2cBRh0mnMXy72L56xguSt4TgrLTdECKDM8huPEtwOkSE4ay00DOYhx8RSuwWj3Ai/Xzk3ngW2Uso1SMjAcOMcGC3VXAK186UnhgQaJ0M/wmgGyPmx8pk0aXB7DjUPcLWqvSzAFaIsV1nK6m0OSX+Pk3rnm23SZ5aVGovT57O0eNC7yYDbXHoSpPst/i3My4qQruw2H0I8AdvYHah/O3P0b5V3oc+sfxml7QEOTbRJuyFi4kkK3mU82vtKyjoF4cl2ORy7UbK5MGOb2olMOaXS8Ac86xKMyY5G2qetq5A94TKE=
*/