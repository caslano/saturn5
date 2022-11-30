// (C) Copyright 2006 Douglas Gregor <doug.gregor -at- gmail.com>

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Douglas Gregor
#ifndef BOOST_MPI_PYTHON_SKELETON_AND_CONTENT_HPP
#define BOOST_MPI_PYTHON_SKELETON_AND_CONTENT_HPP

/** @file skeleton_and_content.hpp
 *
 *  This file reflects the skeleton/content facilities into Python.
 */
#include <boost/python.hpp>
#include <boost/mpi.hpp>
#include <boost/function/function1.hpp>
#define BOOST_MPI_PYTHON_FORWARD_ONLY
#include <boost/mpi/python.hpp>
#include <boost/mpi/python/serialize.hpp>


namespace boost { namespace mpi { namespace python {

/**
 * INTERNAL ONLY
 *
 * This @c content class is a wrapper around the C++ "content"
 * retrieved from get_content. This wrapper is only needed to store a
 * copy of the Python object on which get_content() was called.
 */
class content : public boost::mpi::content
{
  typedef boost::mpi::content inherited;

 public:
  content(const inherited& base, boost::python::object object) 
    : inherited(base), object(object) { }

  inherited&       base()       { return *this; }
  const inherited& base() const { return *this; }

  boost::python::object object;
};

/**
 * INTERNAL ONLY
 *
 * A class specific to the Python bindings that mimics the behavior of
 * the skeleton_proxy<T> template. In the case of Python skeletons, we
 * only need to know the object (and its type) to transmit the
 * skeleton. This is the only user-visible skeleton proxy type,
 * although instantiations of its derived classes (@c
 * skeleton_proxy<T>) will be returned from the Python skeleton()
 * function.
 */
class skeleton_proxy_base 
{
public:
  skeleton_proxy_base(const boost::python::object& object) : object(object) { }

  boost::python::object object;
};

/**
 * INTERNAL ONLY
 *
 * The templated @c skeleton_proxy class represents a skeleton proxy
 * in Python. The only data is stored in the @c skeleton_proxy_base
 * class (which is the type actually exposed as @c skeleton_proxy in
 * Python). However, the type of @c skeleton_proxy<T> is important for
 * (de-)serialization of @c skeleton_proxy<T>'s for transmission.
 */
template<typename T>
class skeleton_proxy : public skeleton_proxy_base
{
 public:
  skeleton_proxy(const boost::python::object& object) 
    : skeleton_proxy_base(object) { }
};

namespace detail {
  using boost::python::object;
  using boost::python::extract;
   
  extern BOOST_MPI_DECL boost::python::object skeleton_proxy_base_type;

  template<typename T>
  struct skeleton_saver
  {
    void 
    operator()(packed_oarchive& ar, const object& obj, const unsigned int)
    {
      packed_skeleton_oarchive pso(ar);
      pso << extract<T&>(obj.attr("object"))();
    }
  };

  template<typename T> 
  struct skeleton_loader
  {
    void 
    operator()(packed_iarchive& ar, object& obj, const unsigned int)
    {
      packed_skeleton_iarchive psi(ar);
      extract<skeleton_proxy<T>&> proxy(obj);
      if (!proxy.check())
        obj = object(skeleton_proxy<T>(object(T())));

      psi >> extract<T&>(obj.attr("object"))();
    }
  };

  /**
   * The @c skeleton_content_handler structure contains all of the
   * information required to extract a skeleton and content from a
   * Python object with a certain C++ type.
   */
  struct skeleton_content_handler {
    function1<object, const object&> get_skeleton_proxy;
    function1<content, const object&> get_content;
  };

  /**
   * A function object that extracts the skeleton from of a Python
   * object, which is actually a wrapped C++ object of type T.
   */
  template<typename T>
  struct do_get_skeleton_proxy
  {
    object operator()(object value) {
      return object(skeleton_proxy<T>(value));
    }
  };

  /**
   * A function object that extracts the content of a Python object,
   * which is actually a wrapped C++ object of type T.
   */
  template<typename T>
  struct do_get_content
  {
    content operator()(object value_obj) {
      T& value = extract<T&>(value_obj)();
      return content(boost::mpi::get_content(value), value_obj);
    }
  };

  /**
   * Determine if a skeleton and content handler for @p type has
   * already been registered.
   */
  BOOST_MPI_PYTHON_DECL bool
  skeleton_and_content_handler_registered(PyTypeObject* type);
 
  /**
   * Register a skeleton/content handler with a particular Python type
   * (which actually wraps a C++ type).
   */
  BOOST_MPI_PYTHON_DECL void 
  register_skeleton_and_content_handler(PyTypeObject*, 
                                        const skeleton_content_handler&);
} // end namespace detail

template<typename T>
void register_skeleton_and_content(const T& value, PyTypeObject* type)
{
  using boost::python::detail::direct_serialization_table;
  using boost::python::detail::get_direct_serialization_table;
  using namespace boost::python;

  // Determine the type
  if (!type)
    type = object(value).ptr()->ob_type;

  // Don't re-register the same type.
  if (detail::skeleton_and_content_handler_registered(type))
    return;

  // Register the skeleton proxy type
  {
    boost::python::scope proxy_scope(detail::skeleton_proxy_base_type);
    std::string name("skeleton_proxy<");
    name += typeid(T).name();
    name += ">";
    class_<skeleton_proxy<T>, bases<skeleton_proxy_base> >(name.c_str(), 
                                                           no_init);
  }

  // Register the saver and loader for the associated skeleton and
  // proxy, to allow (de-)serialization of skeletons via the proxy.
  direct_serialization_table<packed_iarchive, packed_oarchive>& table = 
    get_direct_serialization_table<packed_iarchive, packed_oarchive>();
  table.register_type(detail::skeleton_saver<T>(), 
                      detail::skeleton_loader<T>(), 
                      skeleton_proxy<T>(object(value)));

  // Register the rest of the skeleton/content mechanism, including
  // handlers that extract a skeleton proxy from a Python object and
  // extract the content from a Python object.
  detail::skeleton_content_handler handler;
  handler.get_skeleton_proxy = detail::do_get_skeleton_proxy<T>();
  handler.get_content = detail::do_get_content<T>();
  detail::register_skeleton_and_content_handler(type, handler);
}

} } } // end namespace boost::mpi::python

#endif // BOOST_MPI_PYTHON_SKELETON_AND_CONTENT_HPP

/* skeleton_and_content.hpp
sbFc2MCasBzsfKRh+hT1/DFxTta7xN/Q9V4Bk4VtKfBU0WFiRSoCEY8j3AvS59j9e02BrpZGNiA5MrJRgzJ1E4Hns5yUdxgWractmGBaEnxhcAsixDmM1PjDvVpIoiO2dr0GyQ+XzbpbkGNdg+RBlxR5OBr4mOXjJbm53t5p5UEtLlIsbgFDqvsPmAhqo7rbOMMQmEDUgEd8ldHGwMKSlrteh7YrgpOEYBlNwBTT8Orxq8cFUlYPxmiOOIKBaR5IdGrUue70OI9nbA4qd89R0lOTzSKOEygxtIevajTn4yTP4jkYEcbemV5E5WJb9BsHc8SitB6GEJKhqdQUD6ym5WEyGwXNvn3sPn1RfZCEKOIkwiX35LTjqRBF2QTjWhRljcHOTxTjpE3Zbe/xgVgiKD9lnp09SLDi0/YOPeWi6z8vvzp14VPpL2BNGcR7mvLwx2rszHzxjlxjdT87mr5CuT0i94lGRGq7vUiEch9oNK5Xsl6wI69+hO3YFnDMW/4+fR8iQmmyTl1iTXh6kh9pFmti1R+EJTCUX28s+1SXBTYdob4Q+hBD2BXYtBuRrc0Ly7JroPyQYwmnFH2zuzzhi115g2v4r2dgyIGTcq0AXI7UvGAsM+rTI7irDnb40HWRsP6B3gHAJdmhwo2d9dUpo7IAR3l+eATSUU7SbYjRvQxvuZ5skqwsaNoPWqHInaXSGVcuh7uDH9/PEthmDh7UrUdH5HfC58cxkH/NFslCj4mNvlt26veT5ngokpPz+OfIZZrGaAos5ggiBZm82RK2NLb1o451No/arpBRWXQgGn6XSnK7atuwJ/9GuNxczY4yJMn4HG8KlSC4FMkb6iket4xIdNNl+tr6DObb5P7z0OAubdVnGCe1yRl7EYynp7BYW7N24q2e/gTYdYDzW//XsywEANDPCTXnkn3s6K+OHoVZz53U27E4p7D1jUG7VvWeBJt/aNjJCL+j/jriBdcxqoqrkOR0HsPYlcSegyWvjKbTFTUWaGTuEpeueT92+dlxCGW19mlz9DaGGlw5MCUfjO0LIez1+XOvncq75KU0PtbFErfImh6xmp5TI/vTTcHEu9iQ+ORhYbypu4gTasFVK7SlkLL9bQHe0glhceKUgDqnnIB/y0hXWeoUWei1OLw0ZY/Pijt95CZuSf9iRNBdaKHypll9+bB3a7IyHr0ac0r2GEQywF9HgPMMPH+Q+dLTSlRBi2vDIgInBK1tPcqjuBhDRyVUm8fOSeTRLdDxkeIg/5gqdvwqUSnhfdCaKWGtbF8XdUhFp5RWOGAK7Bdsb5Y/MLdTj6RHdwHqkwFEr9xt5iFXWjoTHjHcg7BUSmSzEmxczWVfwW4POln2LQ1/eiAEGL/7pil+QAkJIKOV5auRIRLqGDcEl39zeRQTOwGPT23Nu4+k9fpWpXJA+zGOfVgB4hgi1m9pcKjKYE2byl15qtOX6K2hUBIdl5rM4HK0Q8pjEqRP4EqyhM3vNRqSu1lIoXo94efIVce5rPujc9H84DJFq/mGIASfaHptv9/wDmWOjwdXBLhUvdX4ojBZVZ4yIfKVrt18egCYxb4EAExM/F1JXIq70Nx9czU4cyc/aXA1ZXZImW2Ip0UXK9nI36ZjFkVc5gd4ssb+K8teNYp7R1HAcG/Cuext/nt4EMKpnSdcHMw8kgeyMuAUUQZEN4ljL9cRu8awb9cPz/588bwjmlQXLedgu6sgh8cGdd0gV4NWPI9E9zXmM7I95KfjU7q9tfnKtBVzpF9UVMxJw4DEVOK+fKnIhRwgNS6zX9jwCtLzbgXn3x8asWZi5F1NPs0xPj37L6KBq91B3dbL/AlLL7Q0u5ZpE/ZLGZ6r5HVjLgzvPc11h1TrF2JyZFPKi2A1O84FrpyApNbNGaR/FDc9CpnxLMI73DzjlnsZStI1HgyeCckdA3946anN5+7wQITZBMzXQhZ+kXr7/TeMvj0ZPDbHA+jucMu+PCcwOWQst6dUh93/lf5bFJu2Hbhwi0+hxySGCoCqEw2cySGrEOcBuYE2qIE/wOFDPFIpYfQYnt9JF93p1K7CLn4qPuS5kD6Fl7DGyXS3VCeyLg1q+0sY5CBAH9YlTrJdSuT7Li81bBMGrAOT93J+4cqJxooi3ZzMXoexQ6ZftdT938d+NUjfcRvUA/pwW0OHqaRLuwZLWq0MGg44gU38Oo9cmHIhFMbGbiMoPktn+6DdRmVfzvFG5iTEGSda94YCBw6GO3zdQOm7ZZTF6k2ZxQz1dKCJLCFE7fMr55ciCDJc7PtTgo0vagBbO8IxC9t52SKtd6VD2Di+cwJmWZYuNLoCcA4koxJcu10LaarKmcmuNXVFxJgcjLtY1nzbs5yfcZta6VG0EydVZ8imbPcNaKnY9yfRVB1lhBP1qxMt4rmVkwjP8qiE/v7WMkR3WAoogWNiGkRMWmRNu9eaJZZxlFMpKzQgS5ejNjTWTm6PJ6eaSst/utRQmaW0cp3FbE+oaF9yav7rr3ROLZIzKvDS84jo8poCfd9rmlvtdpyjy96VruuEcGgwZOXxSVAcL86OiRq4K+e8QcLbwvkOiBSAzenqFZZtHdAqcZhmkuQLF7jmLPZhi5TUxDTXXVJL4ZqyMYHNXEbSaWk/DND9cj7jacnuSi58P9sDKhgC0e40eRjGeirhqWhdhyZM2DpOF7o9A30iNhL39zGSNCGAEcXAoYjKzo0aaImHQxjjfg1e69Vy3rhAh0zE+cekkiDVtegWWDsDu1vFh+idmZ0cdP4vz1zcPXXRV4vuEOP/NX/0xhW/6kivHQ2/7T7EQajHwlHVIlHAn+syE5Jjek6/ZdrvJLK7KVq+4NHB9jq0FHXKhUY8YxVdqadyF6lc38wMB6jYhrOugNBDEiNV0z6d2PxzKeqQwVwmOoa0Bc76FCjRL5VmNBtFNXz2fMd+RzsL8CYBeMpRepXzg9abHuN2wK6Zs6xwHiKirqf9EsVsP1neAXoV10u5ao++tBGJlSpx+vbOQG+Z6Dn2ZUaq784n9CiluRoMrf7Y6/YIbnQcj1iJqtnS4BBKHgXaCSspa9W4Jucb9MnZCLN7DCafNhyY94ELDiFeBNMGmnkysi9gzGu8+QQ4aCs5LP1aZPDqNkFRNKm+kXUPZbdRHxb3TDx/SpPAuZ1B7pukFvOpJVncxqlzo5Ds59a8sWACZ01vs470Yz3hqjgW2DBnjhumNw/PbSvRm/L4D6P3AnSFvHdcPlHjNXsg99sbY1u/tXh/wMkH4OOI6em5smobT8svDS1mre5dch4dNi1F6R+sll1qdDV4yqwuLC+XipldnlCqsb2mDI0s9cQzZ7+6tWMUTvtYJfKuUotqVEOsAfogBFMRTFCquYqdDR/NGVbBfwkdyIJKoTKbfKTrA9Y1L5c608V4JBbQLOtgkzrwVD9BiJVLWW481/OhPZqmPlCBx8mO1Ose1aXJPP5CKJBIA6QRR9dGz3bpdPlL/kZCniWxCt00WByZvcG+oDj7Ax60rzlG5WKBWAopSwdAxCiiYjlzUBjW60XsSgbFrOHeGmNwxGdwOPS/EbsN07HaF8fXQNrowCSavD3ViVhTiifYNofOL8cOCXRYt7o8yQlsBCjbpwfPsIGwF/ivH4sSa/OdfYcTS4OQ4glsJe1KRIHOi1NEKT/He2N+BHwnCYhYfBnqchXytMBZZMcQDshz8GAdHxIejYrOJRpXznnHpyld2oeWLh6yOt3krXTe2K/PIQo7LeNHE/95PNjARfJZX5O+otdWNRx2oE/+0zeZ75tJRlZlwJdib/RMYlDs5RZjHDVaENwn3pPNMEqsGKUsHnC80+6hXi4Ke/CIbEW0U42IiIkq51EziLvnrVuMB+LKxC1U1bkyInqpVUj6rDHhZFwfa+14nYlvSJHzd5PoOIhS+2ztZ3cjNb6kAHs5Jgh9FwR5SlfIjFB9ZTIivonjPSqVYs9TjcgZOG5U3sRmkOcri7F58/sg4V2XAJYdBkYLvdjslJAvFBjuTK7aNgxYm3jbFCTA6jQ/l1k9wGwyh2lhvKTVlxvZreSlvSqEDyTN8CISBHw4B9F7O8xb5BVsJKfArFmIA/GQEoouiZlU0W7xf+wASlCknrFOWHYGhK4RTPqQ7rnIxJBXWG7ZKlUpR6/F6ibI8vA5bcHdY13subJcULKPgxrBuPTxtic2sNrfy1usGCIf8z9UIwfFlkSzlwlu6jEaH5p4N+bpI4HY8bNHwEjJT962fyurcxjyKLCiw8TzuGpn2wtNydJD/fUSBAC/QmKvasuiHrUmyfViFe4ReC2j8ZXowTMAUKOkKwh90lohxt0UgAzSDCcov0R+THvCpbgR0jWurbivsWnrDZB+xjy9q6qEKvJ3PCvU7jgv3QsP5tJcg3EzYyrYSWmksuL1KNRiBo2cNAV45uHJL8a1hOPsnqSR5w2kWYz/ZBkafMsBmif1J+AywKpBsuJePFwcg5LeKrfRuGb3TcKERbq4bgbDxFq1damWdk2milGeBPCLeW9y1RsKtrS4o8FSe6NZL2Pe7G448BTqePT6pFLb8BMjTNEeMqQjxGhLVInBvBgukw2tDlknA1IqKUJl7rHmXMajUpXUSYPRAQPMLNwNng7lOJHNUtyjbk3VbGhWCEp+RDGdvLXMK8SUv/4KiHgKMuoa5I5DdOLp67z0oYiIbFS0WLNhPec3NUsJ0wFyQ+BxU9gOqf0I6OUcn6+STshYoB/PtmmbTOI6bls8q7rMKeyOVXPES3nkCB2QS7LDJiJV4/Wih/bhY7mtKich5XGn3NjxYCi8xhXN8x2/L5u6EbbBmV90B3ukyKgA07/E/VJOpAMgVUeoIHO8HQzrR0LIc3GQOO6UtGj4iLPQzfhmRHnwpJBytd67sPqPftFZvk17xvxtn4lRnXzIGdIP8BeWM4FNrOfkml84kF48V3Xdvne5acmIl3G7ThOadJV8dGQwABEHUI9jeCFRNjtl/9RsGo/UdB3PT8z9+m6UK0EtaSUqyJ88bohIkIfKoQy9WFDp87xQFfFfv29j3eF6b76v/RSg2Al02y2fmfOpz5PLItXReL23zm7gg03dwPPq9ld8/krr6jKvCnHHhLS/674AIRowXAI2a1kIIB3edlShZ60ZHtiTHLUoGutSq/0GWFrIMRxvSyqh+meWJVvHC252tm5jse2DkVEdVZd19T/DbVa9fphimXzhsNmrg8djo5FZyodcslMzM5mJcOl8hwS4fi7897A7xVrDWiL+vflCjkPuZgilH08M1vOu4Vvz+7axs/xzay/1JLUe5hqjHGV4MzAwAUztxNlOIwQUa2G/MnlmSHw7HaN0GfZroRCGUckV58nM8FDsXl1bpSKzZ8lx0tINwMIeABpQZ00EMqq+gRH4zyVL2wLk4+IZqJrfTvroYFMeVDqJFQwZpS+eY9MKcX6atCUixoGHypBpK4ZTmxtwjcr+6+o7I1HECgLUtUIYsF3pAWg36mDAALIQTiTUsU227EuwqZHY9d4TIbIIo7F/UzkpMMaut60ehS4JvjcYAzVdkS8CEliUiePEkrW4L2x6U+nAN7OnX8XdJIkHvAZmFjIiYi/FiqWQUSFoU7XXmPZ75Y0gLE9XRn6QL0w2YOW0bMGeUIFZmhMgi6f19fJXwLPmURpDkpAvFLCRFz7qxbXduCpAa2McGJ1irDARRXJkQtpoTo+GZqwWQx6XZxJXZGuIThwdszpWmLkuZwoacXKz+LFqhDprDrcWEqkB9m7OFE8KOpOrTPmD0yM0yYdTt7OpnfoTYyvy3oFO+/puHwNaAWp6t0eatVGHQmsi48zpNlcsz9jyoXqOYyYs/8kX5i0DqvSarSm/bskLlVHDNO0mszDgKLiVbZyT0P2UCSb0PI4nm+bfCjcWruRQ/PvsZ7VZa+9ycKhk0/9xB8jp2BwlyuhSZsNkyiZ5OG2YBZDNqLlyFssvo0m9lE+2S/JFJXt4IZQL3VWLH5XKDzGhkA5s4NSanSgAXK1CDKaN/IB+owd3OMl0pZxCs5tM8SuDRlbbSHOce60AimLQtQIeD6Ed8FsabCq/JDyEpi89Rps+oJh6L7c+gwO4N0Z4quOumHlR1uN62vUrKN2Glbkzn2rs3whPL5tKiVx6hzzxLGkvABl5fjHxXqHmYBQGQNRevroolA3/pkMKFeHMEq6sJ2Y7KvpdSrGCsG4EWH2V1UvS0ZCtleAAJsB0/+7M8XAYR+mubOzuEYL/qaRHjQ2LzHEi5Mg4YHs26wf6hr89iUFAS4mnnV0CHs0FCwZOd8wxagnCx21V6zsMUDMbQYyGzo2OB9f1K90WaPFfcjROjiw+vN4FYc1ow+vJRqalam2uldENPopGFclM5QaahTja2oSaOrgEV1Bp7loxBaA/RywBTTMxkEc0U6AgyxOIhfYvCJy6VJynnsp3zoF9OSw1tMbR4zjhyXw0gQl2bqx7YIbQRImvazXg4Blr3cpffJr6vCgJrv1IzII6OYj3MqLzvWL++Q2f33fhuSArjEbYKh9kbDbwN83qPWjOD0BWjcr0k2dmupV7IpwAgi4EnhDZwxaM42nX4dxQEjgf+5nqLdwzF8A4ySnAKeIL2dDFdhzMkTSmEJxU46uSrAqZue8JK9MeTeStFLq8FDvYDfByRFVu6y9yVSVD3cgV6QftN9tYmeDGMwH0uAgNiHQYpPL6gOOD4mDhfwPp7WlTHMy3MmfhCjHtDH47t3fwRWqyPFYbETdExfLPBunK+AScOXTq4x9GcJCGg0Ax6blfWICQABX2r/JfTw6fqPlFl0edllVyTKak6wBgiQJKAMMN1fdaMU65wl509DkWR+VjOg2JE9tE3dBUZZ1VR+Yurk/af3wXTaKiy6C79xL+130/bAhw/oY8kQcCkq1bm7uSb96kul14PBYDcpAF6TS720JG5lcubxNtptC5kpSc3nmQwHW12BCQ3cnW+UqK8/K00zy1jEmbX7eSpevA/o+VOEsUO9iQh7/UWuQIFS8Zdd/wrpVqZvqjLuwEJ76IpQOLhfdH54G9YA1IqkxeG8yBhytBZWw6xsiFtu+9PhOU8WEfOajBpivqYCKH9ci6TfXibmUCr8LSDwkhiFD2EAkve1OlZklfHpXcQNHcVIbdI4sv/PU/npRWDUusUARGtcOXNnXgg2C/3was8MTmIJCBF8jEjn03jfA0uY7kGuMBEk9p2MLzVc9/iIFhY2vtcvcSquuQdHX1LEunLyPWuHgtkOwTx+W1ATWLmAgXoQtCvPDOr16YLCtRmIevHvxNuITWU+zJ6AJ0P6K7Lmga+EpM0vvlA+Fagv9+T2YGIfR1QjPKOMysS6hjr9zFz694SOrmUykS7Ck9FFaZOGAwqZH6n/BIegJ4cT0xVCovYgmT6lFDpGa6ejDKusQQ6rBu/wZxdJ+n5D4PLdlw5p7jo+60RXonQQwwc90yxKHFXApwi+/KoqH2M+5DNFnxFg+fuQ0s5deMXCDdX10oXAolIT9R+hR8wjdfxSG7oOj1Zno0k4PsYhgkUXYOr4cJZ+H2ZOMNIc+OGvAZzMiFxnYXji91z8I+4LV1AzODesC4Kvr2CeiFW9yRLGTqAFjhZx+8AmRg4gpmOCQxVvOPjb5NKx+QCG/Q
*/