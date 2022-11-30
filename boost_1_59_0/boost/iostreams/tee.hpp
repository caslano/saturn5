// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2005-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_TEE_HPP_INCLUDED
#define BOOST_IOSTREAMS_TEE_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/assert.hpp>
#include <boost/config.hpp>  // BOOST_DEDUCE_TYPENAME.
#include <boost/iostreams/categories.hpp>
#include <boost/iostreams/detail/adapter/device_adapter.hpp>
#include <boost/iostreams/detail/adapter/filter_adapter.hpp>
#include <boost/iostreams/detail/call_traits.hpp>
#include <boost/iostreams/detail/execute.hpp>
#include <boost/iostreams/detail/functional.hpp>  // call_close_all 
#include <boost/iostreams/operations.hpp>
#include <boost/iostreams/pipeline.hpp>
#include <boost/iostreams/traits.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost { namespace iostreams {

//
// Template name: tee_filter.
// Template parameters:
//      Device - A blocking Sink.
//
template<typename Device>
class tee_filter : public detail::filter_adapter<Device> {
public:
    typedef typename detail::param_type<Device>::type  param_type;
    typedef typename char_type_of<Device>::type        char_type;
    struct category
        : dual_use_filter_tag,
          multichar_tag,
          closable_tag,
          flushable_tag,
          localizable_tag,
          optimally_buffered_tag
        { };

    BOOST_STATIC_ASSERT(is_device<Device>::value);
    BOOST_STATIC_ASSERT((
        is_convertible< // Using mode_of causes failures on VC6-7.0.
            BOOST_DEDUCED_TYPENAME iostreams::category_of<Device>::type, output
        >::value
    ));

    explicit tee_filter(param_type dev) 
        : detail::filter_adapter<Device>(dev) 
        { }

    template<typename Source>
    std::streamsize read(Source& src, char_type* s, std::streamsize n)
    {
        std::streamsize result = iostreams::read(src, s, n);
        if (result != -1) {
            std::streamsize result2 = iostreams::write(this->component(), s, result);
            (void) result2; // Suppress 'unused variable' warning.
            BOOST_ASSERT(result == result2);
        }
        return result;
    }

    template<typename Sink>
    std::streamsize write(Sink& snk, const char_type* s, std::streamsize n)
    {
        std::streamsize result = iostreams::write(snk, s, n);
        std::streamsize result2 = iostreams::write(this->component(), s, result);
        (void) result2; // Suppress 'unused variable' warning.
        BOOST_ASSERT(result == result2);
        return result;
    }

    template<typename Next>
    void close(Next&, BOOST_IOS::openmode)
    { 
        detail::close_all(this->component());
    }

    template<typename Sink>
    bool flush(Sink& snk)
    {
        bool r1 = iostreams::flush(snk);
        bool r2 = iostreams::flush(this->component());
        return r1 && r2;
    }
};
BOOST_IOSTREAMS_PIPABLE(tee_filter, 1)

//
// Template name: tee_device.
// Template parameters:
//      Device - A blocking Device.
//      Sink - A blocking Sink.
//
template<typename Device, typename Sink>
class tee_device {
public:
    typedef typename detail::param_type<Device>::type  device_param;
    typedef typename detail::param_type<Sink>::type    sink_param;
    typedef typename detail::value_type<Device>::type  device_value;
    typedef typename detail::value_type<Sink>::type    sink_value;
    typedef typename char_type_of<Device>::type        char_type;
    typedef typename
            mpl::if_<
                 is_convertible<
                     BOOST_DEDUCED_TYPENAME 
                         iostreams::category_of<Device>::type, 
                     output
                 >,
                 output,
                 input
            >::type                                    mode;
    BOOST_STATIC_ASSERT(is_device<Device>::value);
    BOOST_STATIC_ASSERT(is_device<Sink>::value);
    BOOST_STATIC_ASSERT((
        is_same<
            char_type, 
            BOOST_DEDUCED_TYPENAME char_type_of<Sink>::type
        >::value
    ));
    BOOST_STATIC_ASSERT((
        is_convertible<
            BOOST_DEDUCED_TYPENAME iostreams::category_of<Sink>::type, 
            output
        >::value
    ));
    struct category
        : mode,
          device_tag,
          closable_tag,
          flushable_tag,
          localizable_tag,
          optimally_buffered_tag
        { };
    tee_device(device_param device, sink_param sink) 
        : dev_(device), sink_(sink)
        { }
    std::streamsize read(char_type* s, std::streamsize n)
    {
        BOOST_STATIC_ASSERT((
            is_convertible<
                BOOST_DEDUCED_TYPENAME iostreams::category_of<Device>::type, input
            >::value
        ));
        std::streamsize result1 = iostreams::read(dev_, s, n);
        if (result1 != -1) {
            std::streamsize result2 = iostreams::write(sink_, s, result1);
            (void) result1; // Suppress 'unused variable' warning.
            (void) result2;
            BOOST_ASSERT(result1 == result2);
        }
        return result1;
    }
    std::streamsize write(const char_type* s, std::streamsize n)
    {
        BOOST_STATIC_ASSERT((
            is_convertible<
                BOOST_DEDUCED_TYPENAME iostreams::category_of<Device>::type, output
            >::value
        ));
        std::streamsize result1 = iostreams::write(dev_, s, n);
        std::streamsize result2 = iostreams::write(sink_, s, n);
        (void) result1; // Suppress 'unused variable' warning.
        (void) result2;
        BOOST_ASSERT(result1 == n && result2 == n);
        return n;
    }
    void close()
    {
        detail::execute_all( detail::call_close_all(dev_),
                             detail::call_close_all(sink_) );
    }
    bool flush()
    {
        bool r1 = iostreams::flush(dev_);
        bool r2 = iostreams::flush(sink_);
        return r1 && r2;
    }
    template<typename Locale>
    void imbue(const Locale& loc)
    {
        iostreams::imbue(dev_, loc);
        iostreams::imbue(sink_, loc);
    }
    std::streamsize optimal_buffer_size() const 
    {
        return (std::max) ( iostreams::optimal_buffer_size(dev_), 
                            iostreams::optimal_buffer_size(sink_) );
    }
private:
    device_value  dev_;
    sink_value    sink_;
};

template<typename Sink>
tee_filter<Sink> tee(Sink& snk) 
{ return tee_filter<Sink>(snk); }

template<typename Sink>
tee_filter<Sink> tee(const Sink& snk) 
{ return tee_filter<Sink>(snk); }

template<typename Device, typename Sink>
tee_device<Device, Sink> tee(Device& dev, Sink& sink) 
{ return tee_device<Device, Sink>(dev, sink); }

template<typename Device, typename Sink>
tee_device<Device, Sink> tee(const Device& dev, Sink& sink) 
{ return tee_device<Device, Sink>(dev, sink); }

template<typename Device, typename Sink>
tee_device<Device, Sink> tee(Device& dev, const Sink& sink) 
{ return tee_device<Device, Sink>(dev, sink); }

template<typename Device, typename Sink>
tee_device<Device, Sink> tee(const Device& dev, const Sink& sink) 
{ return tee_device<Device, Sink>(dev, sink); }

} } // End namespaces iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_TEE_HPP_INCLUDED

/* tee.hpp
P6G2V6po0YKiCiydsjYu3cEf5msuQIB2kw27CVjowkgf1SWvt+nQEtcXS5CQ9jZ95a8YxEkgnDFMA60tGNabuivadUGMgG8EOmUqHrhrQ8tE6yWP0kVmB9s0i4xvRgjq0Bt08PgzjHCf9K49TuKVlVVHQ9Xrj8mdR70B6LjNA3sJmJrUvXzhiGG52HYQjq24LT46i+5rQKehAFz/iaqNbNCBjVs0K3JJ+8I2nJFuMXuiFLxBy48p9qxPG5NPGywPFQBjxW0BF0bN7QkzzyUeL/X8oizzxJveBajs5FX0Bet4wa5O7hkPaS0NIVqlg3mlMPUr9wOII4lPsOomPk6x5114Ra7GRtbHVGb6UXJDSt+LYrcXzpnDIfhXdoF12Hdh8GH97eFD6T2e5spzKhjPTY4d1SPSw3/Gcdpl+sZsel5MqSMjRkLwVXOAA0yO8JZdFK4IYX1T22v/VOxu4Lp0WidBSU2OD2NFvQlmu4kapnaDBFjvBOrrLo8NigrIvxHfIYAaJ5voq34m+OYhp894KOY8pk6H9jErd7IW1o/0AsAhPvVgVKW/JVL5zXS1xjniw7inOqGdFuvfJkTrZuOz9gOVur3xhOco/tKiuJLVZi138xW2uAl1ycf1sWr8Letfm38gL1APVzqMnQC5hE6EKzqF91LIXCELSvghLvq8ay6U355vZxMY4SPfXZWSjEXe3aI77DZ+bYSH1wZdfOOAwPQaB1OaDTKJz0FjXdost1QvYJUAld5TSJqve+ojiYp1YsyAW4llTiAEgh03SyPBJkVbt1PdVSYV8b0AaTjCTgpQSZh1OrRKhAH8C4bNzCuCfK/ILNU29WDf9RM6ZhTXWAhmF8eb0I2uX/J8LR929RU5SVCwjbg8ryVz8ehiAdsiCBtvPEI548t1MvI89NAiuyjj7vs27WdMoIwkhL+q8xDPexwEMlcN1hHRshpG/PcfG2lgUH4CojBMRruyCk6e82Qa3C3cN8KANClXGsFHC0+VCU+XnKOsQznYo3nlaeA7g0L9g1dipLeqnb8UKUdoDfNDdwisaS0k8tuKzRsetBMrzM3r94Hi9n3KAuhkbZtkxOuY66xiTqsztxALSTI3rm9bqAVQjtwX1L5W+L2A+wI/+Z92DIl6oGxeuzVx4Cf8GVNd2Ogre6qpFb0c2BmLoit80EqEA3GXXgjmhj8wIJWmyZiBfLF5Aou1GcwNbp5EZSt5aVMhAjLk50j9DY/V5tTJ32Vf7KLbLZtUzTzo/3Z8ucMRRNENl79W6VV9SPPvYLtsIPk6K62pZ4xQCAIqDJU/+jOTsKCgEjQYMSwULn0tCrnH3rITRSk2j/GeRfhS2d4LCE0ffV/uuDs0IOt8XCldp6Os02afIDbevjBRJpuBPZcOp3/+MiW4c/W0V1At7ZpiR7NlYLLMdrSugKdpYynDUM8LlkwNusC/FGWDgy+E66WtbYUylcqTv+JTPkw44q6+q7EdVHXJty8qKq+FXy5tFF376wFmmeadKwWh01jZAAug8CPj1jkXO8SI8QnqQttnGJBWwAnKBNUPGff2bHKdND0AV4H7U0x9EuzTz9JNEohLiHWGyoViv+9cS+5xVk0tQ/5u21h6UmOSXAABm4unQnIZ8fpK1DqclfUVlKjXpPzd59Xo/9Y7e47YhVZkpkf+yQaxGIi8W8VhZNtww1TcCNtshXQi1Orqxlm2sgnYGZwcmJKpHaTYE0cRzZ7TFiVT0HE3MCoBH/X9oz/6Jpobj3sgu1fSNqW408rDVKplOapnPAtscN2MjtSYF0mxuqk3Q5ZaEaxoetYv24RIILpD77AgtxD3kNMQNTKbk+ynN5FibVEWLlDhGhq6nuGLh+LM5RIxuSM0ZScIB2xhDnWpyzeVA8nufc6uvujVZl0KEgwqK9C2qIYPvkHX1pSJybiYfLk41nUy7oyHwvvShA6XMatu2EvX1gI7vZatNNtQRopZs1s0uF9784rWZDEhceTtXa0C3Q/GOJFeP+J08pepeYibj2apvXurtR5qama6lrBgeAhgj3w0/qTrDJDN3e7ZDbR6xyhXJzQShmv1rE3N/R091ciT+ebBtx/eJkV7G88wqS9pwUNrHdL3pCyaJJ3wtRMS0yf6NrAKfDJrcu0IR4d8rra+elNgwJ/0pOwG0dENSVauOZaR9N+aA+ZRxhr6u6TPE6fHbXhUV+JxsyeYE4ma/TfTLWsyqg0psUVPAlqYMSlo+if3Y4AHzKjTZ3DlHyFxTvBo6i3cEIp6+iZzxi2BvrHtD7tkU4hHz5IrCV+1sGq/OuBimTCTW5tmKdnVVDftOfmxJ0O/tZkNyrYeCGMzGLwSFUy7cKyHJkifKAXeoP3OUVNhC9zWnhQBVMs7vvwLLvPIVftxiaDCGrtLjiUS0tNAiqOVMMz1Wy6Vrk2vbfJv73R3ZQRa+Sm6cAHrvdyQLbh4G9trAUjjefIUYGWrtgFI466mlmvu5GxzIHO8N9UINajh6KWMn4nMocMPU5LwFtunNJ15B4EM1ukwXjWPFcOhUY12q2i4z2fTBCmr1WcnBjiDjM1Pf2mjS46Pk1ohmonP+D4SyKxn+HMrwzYOIgLXSWX6/KKewcFStetDPof0PDoZHVD7Q6gBFlWgxzM//+9offdva7y9iYumoBg1XN3F/WGt6375RBtW9UDIDGlYTr9vpRhmCzQ2EzhZ7CUXFzLO10I/6txYgcKEsanZGg8ua9uHQgNp1OQI1XOTv9ugYiElOiMkGbFAph/eLs6geCHHu95ChSF881phEdJq/tUrUs0BCbyU4voTTI5ao+MuRkk+GHUZydCqVoJ69m1iItDFByHQnJZBw6z7THgLme/O5/Kq6Rloe208bq5VfM8sh/zkACWHLepKNGiP4/jH42OOjRgci1oCMZvADy5/NMrxmIix6BjrBiwe91tKQMquAeH2a+IBKVxe+ep+8ugVd/7BKtNQ+sh99GcEHrlJVUEBQNODXtkIrfUl+60GApAASGWvpOVC8wYnu9LWGPRPUmzHRx9VBRZ778min3YQMdqEJQ3GbLlr3qgE8Ns+3yzgQ2puxrFX+hZ5IbwCqEJWShf+NYyoznHU9MshEuuQfxIxJqJpvcIiLnjcrwapGPNI54zKpQtlRrCnyWKJSXFRC9tOLfzbnt/ErfNGdYyGIfMWqhAVLzLBIVtdeqQzjW8v6XTcyR3EhcTvHGHttLcffGuJjFEPSbniFflV75LMJdouCJEoTHN20k2D1SgH1kR5+KOmbyCQ52rMEEAfmqnVFc3AU063txfLKx+AsYvjIvN5HPumz+EW62b6JVSgdYxnpVCeeOf0fFc9T+S4vMtHHYjCf+JMzWbvySI33+WLx9eBtwLDItWBXJLQVFugyudJTgalhvTvjyd5WhZjAskIL+9LaIYSKEBo6wuwaJ9bP7U1Bdz6dq/EZ/Lo6BixJjrfKTLP02B5zarsqorJKTfgl5flcrArAu/gtkjXN4GtHAQ7HBxWpD5rrsP9Oi3Q/B4cQL2yRVbibie0VgEA85+WoxWPOXCPKqRR8GzXQQWiD3boELjFEKAUS2jM3J6TfegBJ2xPeSPhxPrnxmEBgxlMbX9AjsFawVDF57+ATQ5PBFK4BOdyKLvQx0keP6fVayfpBCKzxLS9ZSYX7jWy3XMPm5qAqpTN4vgPoTlWh6NGoHJ1ZxXLtWppWUEFurzI62H4qQOGd2e1RBipHcMBpJ6kPfw0HpXrcM0QylKAUOYYV//AGIxTw3ZXM5qNSD4mF/gLAmkLOh5HrrSF63y3tVyAs6duG/Lsnplsef8cn8c9nIMsfj5GZ20l+xXuA3aKXfIEXmRvAaPO/N1nTdFfeGg9KCKk3JYCvdmICbqvUBOOsA9hyh7UHUHlk5rNU5v1Qv5A/C4VVcZpaLlI1B+zBtiB02AUUP1u0zQe7IUTF+1ku2kOsIcEr7lMB57mJe+nI/3nBpt2znGDR2d6Ce6NTmvaEXUbyzrDQQROCHHV1em6KyJZQgZytZkbo0cDA63sbWNZ4yDcSWT1Y53lfSgPI/GyZGf/YlnHqYF0l9Ae5i7WbvcApYCI+rcxdCGo9MhXfYZuElizeO80CVx7kvuDSCUvXN1ZfNJk03D/MRdrty6dXF90gIu6+xSu6TLxIDYWv62n40SGu1ydlaXDYIKo0YB7LSHVoQ5fUWji5E+3VFCNymhNsYw3tNQ5GbLcnGWX1Sr22dRNYBUeJOmPE9xADku1NNkfae9oBjkv4iscjsKo7mBpV5ZQlDiCBN/7dxixkGQVuxXjEzGchJ7vSckPh70giTrBjx0zJ6rQADLvwf1OHny5P5zs7l5GHXuy7CN28iAaqsPIJMJ00qlaEeTjNe/6Mjf6/dcwHvZn7gMke2ikqMQpQr1kpI3MkvNlSuS6LqHGMO+eNuPIOeyhakOI4sD63xyl8l/RLc6n5N2MpkPRcHd0uXlccCcGFA2gwSkNWA//xvJenp/u3WrUIhO2L3zxurNfjdKysrj9pcPKEXJsW5E4lTM1qSWeh0pZNsqv1GQ36YRoDdKiUER9xRk4O3doI/odtkPmuGX56riwRhClB9g9TudsgzAKKs+qy+k1c8pZJaQvVrIMjmTxuuJXKKz/NA/jTDteYxqbIYaST9HvGDYIGcSYrxs2KihuI8TXicjzzQDfozRxQrsnKq0s2KcWEp1gQDV71fjN36Twpp27m+4+AhHE8Z3dbgx87dbY05Dj/zR2t7ElAasqYE4mOBBRxE1xK9tTVetsmmQABCz706rlhSgHup4EWopeDte62vtdPzv+8Di0014RIwyS27TZkmVSUhACDWghKDWC3Q1NTzHnoy1FKH47Ncp49oedvzmd1kK55AgdW5/tRxbV8BpCqHlmSOD2VVPNEjR17s7RDUSKf7vWUiUkBQ3LkYULDnL9KNlAjI9Hq9luZ8blr1TYgpU4PK7ZWzWHswvBHv9DgRujOQQWFOrTMZvtHDvKRjhPiNxHaFBsENNq22Ep4srDVdEUmHg/RPdQaQDh9onzksOklImo8GSxGmffFljyI/zKeDqpJp9J/NGmsH4h7R7CwnjBLOwVV9VYBY2QE95BbrTdJVj+mgwXDh/a3OhZ/4L7roZ4ugl00mTfO/vxqFIJoeUzjCiThvNZvYUeoC0n1RDCycEcR9FoHTp+Ocb/sBXNeXDxPt4IgDLaaO+sOEBehtcM5UJzBWBdApmVGWZKgZcrwUQbR/y6JdxJTVLeVk6I5nXGC9wy2Pl85dBA7ktlGKy7NGKYUJIcvM5Tfziut6yraaMHpmoAZ/m7Apff9/l97RZIvfNCw74zMrm0kHgSoJNeGM9X+OFDle0Pw1MMHCtuTUUBLD6a9caEJWWNE3f5GDyR6+ECLBdd3wfjbukmCn0yF42zhh9mb9ZXAC2MPd7QdAx7AHNCTe6KEHrM8/jzaDigA1h84YdNeXeUxyd55/tQoEOc9Hdi+3NSSfpNJEy3ieu5Tsm/yIrwbpA54ibJh/KfHwtbmG31u3Ov/Sc2jnhXm/PO4iGgdLKwT6kk116cd89XY7Laa5d/VNQ5TndE9uwNpkUdzp9YfoGIJ8IUVZmhO0Y1RUff9G7ha2Q60dRRazhSDViBQmXIT2G4HCnucvZjhC+pXJdYyT0Uc65YsUa6nqGDlXyZgowQpR+itzqzo9GJO47Rh80oN+vrGcmcTWicOIb1cXxslLQKxSisT8rNFLugd09/3on4MTJWEvjlPL7+0iC2hlog7heAoTfE4vd4v4+rlZFQqBTbIfr+pySZaZ5Y7Y5/rNEATs7WlEwBANiZYSw+5MQAzPCWUeunAL78pN6nrQh9x0uYVFe0o1DF++PXlEt1oIqhMXd/D6J8I1MHmuBUFMkT+wm5BVgMRxrUmKHPTp5WUtfZbyOfFJ6Nn76GJcggpB+wUhutl9Wpx1vL85+JYi356j1DAQbaq24skyaiEvduCZhDOCFbJ7Bf0yddf6YRuhylfWRwdA57aSX298p8iyQzLPE4b/H+jSnWy6HPbQqN6M52fO2JJSSvRDWEVlpobs7DM9htHyXBKabOj8GMIqYCYQga5mO8CFWdSqsfBl6apwLTDDNOG6ieNkqu1E6He4jcffZg/Vki4H59a6d15vixco8m2+78waQWwdmMWyFypBTFtSJ6DrXnFWC4JzRJObarx8MpSHjogbQVVYzMlJ9awQk67oVIHdLen9rbHSZB62d6bRkJrrHWZkNkPBX3bdfdiVywF8LRtTofqefNwiBkBuMQf+xbue+ZcTtMWVjBp/fL/wTb5GAkXlgktyPH9HW2dgSHLMySg5xK2kxMVO0gdXdwqx++KE97WzstSgG0UedS2RK69a5wg9jYkiQNhXQWfjWR6wGMqiVJFOR4L9yLF3SgGLll8rETliWdUVbVo185zdfJlVOwb0x8wh1T86cCn3go+GLbZvY/iKKf0IbUN6aJT2C1dkyxpR8qEd5fVONytvCFBL9V3yDzOMvdrF69VRuDtMSSlJWZJwtWNiZLLPIXS5+mNvGMnvsTS8VK+Z6DKW8bZEwz6n3wMWIR+SK3nK7Dg9GB6AIbU3BXDE2GCbes6hCa6wQtzFydT8CSoECaCNUup/0udQvA2Qf7dvZeb8v25CwVLLx+XLEk8o0EydO9We2Wgp54v6bMktX2CHoIz8/T3yguwBpflpIT3P7efMJqHelPBZe9ualfBYTXrsCjM4o4/RGmgZ8rPcr5UxaFrd125KERIQ7Zj9jNIg/ENKwln0C8PjCoBcIJ/I+dL9I97cRgwpQm5tI7kQTm9QClhMQT4ACsLT3kB4hYJjYxO4BgsBMibVg0dQ+7zFmrDfbor3NlT56z3DGRJwO4BjPL/Su0HolYyJ8RVjFepJzOCvE+I5AOz7CQ6kaeTUPAJh92icjpl1Z2VBWNk4fjoWJVLgihXueje/RyKBtqvlWm7aP61ywvun40DD4Lk+q6JB86QocwhqDMjk2ExRXR1Wr37Sq1q6BB+lrde+YkIkw9znvM5V7uNxQZmayGVnJHOnNK7ujGS2t108SjHB7aWaCIucLXfhcBbEqCXGUZQUcC+j8HazVe7k0KFAtuaGgljI8sUmSMd461yurMFScf7ruBAjTp7bVc26LDbsS5ygmGoUoCYQ9ajBMhgw0iZz3h6OoLoxHwCx4fBwAGnACdPBiRs/g4HNAM9wP5f6tZ0ZlkP1De2cuy26AAdEqP+7jFUwL2BGwtCsyxlhQLJF5e9wMYYW2qfdI6QdjU1wfwtYJMwsmzgGq04zmxOqw4V1q9gZ0Jgh0SXe6WrarJNJDj2nK5K/ggTjK6Q5t8NSBWIA1Z/OJSQUC1OwEPX6ijg73VxD9eb4QhYdbSY618tNiYPy+KaPNikLhK1WRpzADpF+DGT/cVkZNMaDVqrTg8vfJy9B7HU2DklVmijSs7SJG3SbZJmDADB9X1NPJXC+c9CBKQxG7Z/9U8dW0sj/wN36WxWL6oWetoROn32asUkrV5s7vRzezwRBvPMuf5cOQ5Gk6QAGkmq6sxJEm98k+3DJLDo6gq2y7vmktPngleZMEEKch01YEKsll1sy8wI69QTwMqrRkozgRw7fTCjhtPqIr625F/WwtM309PONL9trd0
*/