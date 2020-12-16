//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_EXCEPTION_CONTEXT_ERROR_HPP
#define BOOST_COMPUTE_EXCEPTION_CONTEXT_ERROR_HPP

#include <exception>

namespace boost {
namespace compute {

class context;

/// \class context_error
/// \brief A run-time OpenCL context error.
///
/// The context_error exception is thrown when the OpenCL context encounters
/// an error condition. Boost.Compute is notified of these error conditions by
/// registering an error handler when creating context objects (via the
/// \c pfn_notify argument to the \c clCreateContext() function).
///
/// This exception is different than the opencl_error exception which is thrown
/// as a result of error caused when calling a single OpenCL API function.
///
/// \see opencl_error
class context_error : public std::exception
{
public:
    /// Creates a new context error exception object.
    context_error(const context *context,
                  const char *errinfo,
                  const void *private_info,
                  size_t private_info_size) throw()
        : m_context(context),
          m_errinfo(errinfo),
          m_private_info(private_info),
          m_private_info_size(private_info_size)
    {
    }

    /// Destroys the context error object.
    ~context_error() throw()
    {
    }

    /// Returns a string with a description of the error.
    const char* what() const throw()
    {
        return m_errinfo;
    }

    /// Returns a pointer to the context object which generated the error
    /// notification.
    const context* get_context_ptr() const throw()
    {
        return m_context;
    }

    /// Returns a pointer to the private info memory block.
    const void* get_private_info_ptr() const throw()
    {
        return m_private_info;
    }

    /// Returns the size of the private info memory block.
    size_t get_private_info_size() const throw()
    {
        return m_private_info_size;
    }

private:
    const context *m_context;
    const char *m_errinfo;
    const void *m_private_info;
    size_t m_private_info_size;
};

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_EXCEPTION_CONTEXT_ERROR_HPP

/* context_error.hpp
k5zJl87Uhj3IuG6cNVZ9HMHWzjU35KfpN8yPTvD8gHl38h1yW8o+PXNRaFHGz9nBAeS0gIzM53OvKtNvXMFJ/E9+kxG/08oI4uwqz3bO4F/Pke3e7EHcTYlLefrMN40xHxd7+6zzWgsrsvXk45XeWyED/3ff++pyQ/37k3r2p9Pfkcvx9H3cCHtKkmG7cWGvjfVL3c/HxDf2v6/2zrOut5u+XaeuTZRlXlY4nezXkcfzoTjLv9lnw9xxdO+eNnFzUeh3PD43z1zIseBZdRS8P3Kvtp6jjV+yySH6tAaT8bxtRC7F3aynqD+5i/jqebDoM+O6eBc4l7uHfZ7o2DvWjaboW5pNWT8ufKvfL42zNiI+tWtzvfyzUZsvMs7y8cJKMl+sXevIeTX/tad45n5l0ntUTZbKSVtfT3Tru7WXDNmUcmz4JHZhzTVB/kXXBWvYbYzd+K0vOpws0+KPeVKJjEvXisd59rAPGfRNkD+Tk+c8Vnm+LPeK+8x1o23Y8zh9n2/eJm/KzNP+0fqtv5kF5CDGtd0iRkyTg12qrT36sNbxj+USxtnckFi5Izs8kf2fos9st9f8K90sjsuxQnO1aCtj59ZyjPqY9x7ZKUpiRvFadmHuUPwtn95a2xaR/wztVF65Hs+I9Sh4n6zcJdbO1T42lSGbaDN9+0vMuG39oMt4eoS4+JW2vS/+HEMG+7LFJjL4KV99O+ZdAt/n6vM6c5hv6OJH+mROmzAfjyrZGBvJk016BzK/ll/fYwxbwwaeob+T5Xc3iXl7jVKfuCu/L9TwYzEwcZL8wDMBOe+xlOYYK10fnkO3jxinS+5ZqV/6XdTnNIKt1bmCHTWbZy1m8zuq23MF2SPYxUj1bM0H95Trt7n2IePYdeyq1ph0NnmcJCfsAd3k2X0xKx6x5Ui754uFDXSaE69Ts+hlBbkuUbe13kI7+5pLP0ly8sydAdrzInRGzsUx/Nf54vtksgu71v70PDZ9Cv8TP6Mz5E95ehOrsnONTe+KI/VsynpfmTwC688J87T0B3S/hN/tLr7oZwblW+nJul/ZGmaiih7T+veENrgmVSZLz37a18C8x/ld9Mf6bmFr516usMap7+aRKblF3ve0Zy0zflNfyE/zn2jzK+Kk48FM/f1EG8kobT026XiGrgPtj1pHmIfyCfsnFF2bXsr2DjFm+u0lMYOMNohhp6vvUjHU77C5uDFqSO5kHpM8Q+yTv1vgkq+7hs2nlrDhF52v1zf9y6IoZpZLMf6g7vPFlKeMUQO+H6X9pUpzFvI+0fdR/q6VV09yz66V9vNiZwfRo7Zl6KThTrnh39nnV8bh79S3nVzMnhv0GkT7su2CsWUnxy8wf35Z/tvvuQl5epjXh9P0dVj+fK/+iWGpL8n2LbGyx3g4a2M+zmfm0N0adrqVzzFiOftTtucxtOUZcqTzUoaeF4w2vrLrY7VX7CznXavOxIn6M5WPuC+YZ971Lbk/aOytJgt76mTlTomz5EyXsB1jRV7fCqGYZQ2/6Jm14qViVIqt7kpectWC2JTw22LeuQgFZSZmeB41qvSbrZhkj9Fyo3ZdSv5ia0Z+lc26bqL6kOBjqbcqxDx5gPl/QjsyaX5n//ACOYQfVBgnfZJ9QflF9+Q+cn+j+dh3I/WfD29iDL2HPF/gm+alibFsebU4HBcDr3JsC9eMVm/E9r9/L2yZPlgXDNUVzZYfeU+puCM9lshIThstYeOn8Ner+N6BrpvLnuNiCpvI7VNpr3YyO0sMe5ev/5e9846Tq6ri+CUmMSEBhhLsuthBgcmGhKCim7LACknWZAMEhdk2ya7Z8tiZDQmKLPYGDPbu2sU6dsG2dhTFBcFexl4=
*/