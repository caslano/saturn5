// Copyright Gottfried Ganßauge 2003..2006.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
/*
 * Generic Conversion of opaque C++-pointers to a Python-Wrapper.
 */
# ifndef OPAQUE_POINTER_CONVERTER_HPP_
# define OPAQUE_POINTER_CONVERTER_HPP_

# include <boost/python/detail/prefix.hpp>
# include <boost/python/lvalue_from_pytype.hpp>
# include <boost/python/to_python_converter.hpp>
# include <boost/python/converter/registrations.hpp>
# include <boost/python/detail/dealloc.hpp>
# include <boost/python/detail/type_traits.hpp>
# include <boost/python/detail/none.hpp>
# include <boost/python/type_id.hpp>
# include <boost/python/errors.hpp>

# include <boost/implicit_cast.hpp>

# include <boost/mpl/eval_if.hpp>
# include <boost/mpl/identity.hpp>
# include <boost/mpl/assert.hpp>

// opaque --
//
// registers to- and from- python conversions for a type Pointee.
//
// Note:
// In addition you need to define specializations for type_id
// on the type pointed to by Pointer using
// BOOST_PYTHON_OPAQUE_SPECIALIZED_TYPE_ID(Pointee)
//
// For an example see libs/python/test/opaque.cpp
//
namespace boost { namespace python {

template <class Pointee>
struct opaque
{
    opaque()
    {
        if (type_object.tp_name == 0)
        {
            type_object.tp_name = const_cast<char*>(type_id<Pointee*>().name());
            if (PyType_Ready (&type_object) < 0)
            {
                throw error_already_set();
            }

            this->register_self();
        }
    }
    
    static opaque instance;
private:
    
    static void* extract(PyObject* op)
    {
        return PyObject_TypeCheck(op, &type_object)
            ? static_cast<python_instance*>(implicit_cast<void*>(op))->x
            : 0
            ;
    }

    static PyObject* wrap(void const* px)
    {
        Pointee* x = *static_cast<Pointee*const*>(px);
        
        if (x == 0)
            return detail::none();

        if ( python_instance *o = PyObject_New(python_instance, &type_object) )
        {
            o->x = x;
            return static_cast<PyObject*>(implicit_cast<void*>(o));
        }
        else
        {
            throw error_already_set();
        }
    }

    void register_self()
    {
        converter::registration const *existing =
            converter::registry::query (type_id<Pointee*>());

        if ((existing == 0) || (existing->m_to_python == 0))
        {
#ifndef BOOST_PYTHON_NO_PY_SIGNATURES
            converter::registry::insert(&extract, type_id<Pointee>(), &get_pytype);
            converter::registry::insert(&wrap, type_id<Pointee*>(), &get_pytype);
#else
            converter::registry::insert(&extract, type_id<Pointee>());
            converter::registry::insert(&wrap, type_id<Pointee*>());
#endif
        }
    }

    struct python_instance
    {
        PyObject_HEAD
        Pointee* x;
    };
    
    static PyTypeObject type_object;
#ifndef BOOST_PYTHON_NO_PY_SIGNATURES
    static PyTypeObject const *get_pytype(){return  &type_object; }
#endif
};

template <class Pointee>
opaque<Pointee> opaque<Pointee>::instance;

template <class Pointee>
PyTypeObject opaque<Pointee>::type_object =
{
    PyVarObject_HEAD_INIT(NULL, 0)
    0,
    sizeof( BOOST_DEDUCED_TYPENAME opaque<Pointee>::python_instance ),
    0,
    ::boost::python::detail::dealloc,
    0,          /* tp_print */
    0,          /* tp_getattr */
    0,          /* tp_setattr */
    0,          /* tp_compare */
    0,          /* tp_repr */
    0,          /* tp_as_number */
    0,          /* tp_as_sequence */
    0,          /* tp_as_mapping */
    0,          /* tp_hash */
    0,          /* tp_call */
    0,          /* tp_str */
    0,          /* tp_getattro */
    0,          /* tp_setattro */
    0,          /* tp_as_buffer */
    0,          /* tp_flags */
    0,          /* tp_doc */
    0,          /* tp_traverse */
    0,          /* tp_clear */
    0,          /* tp_richcompare */
    0,          /* tp_weaklistoffset */
    0,          /* tp_iter */
    0,          /* tp_iternext */
    0,          /* tp_methods */
    0,          /* tp_members */
    0,          /* tp_getset */
    0,          /* tp_base */
    0,          /* tp_dict */
    0,          /* tp_descr_get */
    0,          /* tp_descr_set */
    0,          /* tp_dictoffset */
    0,          /* tp_init */
    0,          /* tp_alloc */
    0,          /* tp_new */
    0,          /* tp_free */
    0,          /* tp_is_gc */
    0,          /* tp_bases */
    0,          /* tp_mro */
    0,          /* tp_cache */
    0,          /* tp_subclasses */
    0,          /* tp_weaklist */
#if PYTHON_API_VERSION >= 1012
    0           /* tp_del */
#endif
};
}} // namespace boost::python

// If you change the below, don't forget to alter the end of type_id.hpp
#   define BOOST_PYTHON_OPAQUE_SPECIALIZED_TYPE_ID(Pointee)                     \
    namespace boost { namespace python {                                        \
    template<>                                                                  \
    inline type_info type_id<Pointee>()                                         \
    {                                                                           \
        return type_info (typeid (Pointee *));                                  \
    }                                                                           \
    template<>                                                                  \
    inline type_info type_id<const volatile Pointee&>()                         \
    {                                                                           \
        return type_info (typeid (Pointee *));                                  \
    }                                                                           \
    }}

# endif    // OPAQUE_POINTER_CONVERTER_HPP_

/* opaque_pointer_converter.hpp
9R+RhFhVSIREa9zdw0MleWt9nYDWautkeB/3zTM53CFgsujHIfputGh3QagWiZNH/Y4QmSEGLyPMx9/tg7SSK1OtqzQEL1XXivnEJJxETFQlRbBs0cfzq8tHVGQv6DceG4Mw1g4xngnJbmiWijzBDsX8Hvowg9bn3Bx8j8uS6v3UbA7l04FRSE0J5Qe+WoDLzdovknSZZFbfFwHuF/mqroXTFb7DwY5v1kygpQp/cqbrnd6fBWviM3m+U+JcNmqCPrkZ7XQ5zaqTBthgk5JD1shm/ZImfWyXTlWnTrpN69zVIXzx29Py8F5VIiNsrLNDQ29l2oQcg/mZb5eHFVCpEUEke1fsyyTNzaPmBZ0tBuyUABlswwGxwUrrm7XC8nD+TvwyrfVVuHL9Lrj7+dhrFAyJ6AduxZ89x5aVHVTz+Z8crL6Y6JoP3GmL5bJyu6phl7r9v7KoG2Tyr/rbMSPc1UUHpeOR5GkOG4bEWNXBGuup7wPuUJIRo6/7g/YKl5meUvmKYfdnVvg4xPvh81O1NxOCHZp5AVfo+kxnEgMw94O7NCdRNYjsc0qVTKVMPxUPxid8uQmrdgYV5HuRBlTEaPhYJLSIyXqPNiZp5PcnzaVsyzs4wrTWphKBk2kD8UO2E9VqHoE7nTH1mtjbo5zKwS90zD9vrdHjhspEO1f90sexlxONQxHJDYOLRpKHQ6if5uiWwWIKUBf+1bRz6c6ZlaoJ3df65qSwkBeXtdNYexUmbBRREjSYh8walMm9RbAN/M/KWqN3WWIEnMI5JeWGZblgaXzNPHucMnp1RKxhHfq4I1v87E6ZuaCAd1raj0LOCnglPWPVj5IWDC250XdKjUtppgZWD8qUZYWNaU67LLaBGBEYmdGWDVS4McEMlPgpmMgfY/XXIU0Tev3sPB2Fpg/tuXbeBx5m9FNFdR596g0ccHv6sS96JZhynvQg5D9RrPFkAd8QxtW6kSv33el2MKlUtsvdNYss5eUQOzLwralHF7dtG3QIj9IANighVaHiPoeDunGH5hwpporQ/m9jPAMrRBTZKOnOoapiOU7XO9bYhOFYotIDOW96cRyDrOF2t6p4slWSM0gSBVHzxGE+sSENuarWSD3l06r6QX+qK5TTSu4txS9wcvP0JNJHyMdki/Vgkxb5GaVyFc8+p5tH0dKKy5iypgsLO3HjkfVWVWRUVLN1R4Ie+TdnOxPT+yOKGpZmaD/ewvj3Lyi3FJuPMVtzl4F6lYuFy6/Sgy5s/Elg3Jp9tLFD6UzwaRxC2QfqEwgdK0Lkr1buAEh5V3c3fiaY6asly3eDTwRII/KiNJ/r0P+6BTPBWuJ+z4Qh+DJCKFoEUwf7FyOYCYbqI/6ctkP0+338iMwNKSKQ6iQ+TYadFNGXaiPeVsadBNGLaiaeV6aOGNGdajD+9LChXGSsqQkqgG3ODUJEKEj56YCEWFD124CD4goU8yFyPyym/QWOSHQm83r56G5rYO2GngFFXMOQT5MXUs0Xemt5FZ1vXjJ6pak2841QLiaXYieASlCCPDoI/gldn02EEYmj9mz2EL5hUuPpqCv+ccnwjSJ0Vp1Pkz9ZTilsfbYU5V+1dJ8BwzS5Ky71D07Vbs7C7x9ry2gMWadI170wHIljX8t+JGbANsr9asZO8Pmyz4l6M5nn3lsoTlD1hR/+33X6F7aTb2OSGmOaeCPlleffXFv31zyDA1ClxJACkyWV4FKRVauurJDohUj+GZXqBk/8ErwCR51Os4B5XfmuJs86CuZ/jCXy0h+gTvfLltONhbkHQ2re9W+UaPZzZqqs2DSxG4TwpSnw/YR/qff7IYcmXFcjuP9U+9Jyss/o6MJ9h9xkyZ/8lU99XrrkKKjLJVRM/tt+0qePM0P3UQOkk9/EDOg5ozCI83ilr/jIlm2Fl04Bf59B9v1fyvD2c2kaFYo8VVUugnirHAOPmxdoh2cpvJ0VKZmHuy6uUju2iNODuFjILRsHxJz5gjgU6MdQUTPEiNxHDCdC7gpEJkkMPrQ/gsYTwuDiKqCibuG8isQs2lEWg3sDiQMaA6O7nG6hvAYVOGDco6iogcLdkF33a/Vr9mv3a/lrwuujXdTdyd3K3Yvdjd33XaRrDLeYpz9P0U8dT3VPbS3K/gaOmDyRmQMqAzvujYLawsrCcsJSOUwqiTYj9Qf6z46Arg5ZYwYTOtZU1mTWRNbU6qTq+CCWre9bTFsMWyxbzGFi/9bdTG6YbpjuDY/1LlvnEyHUV3WPmAA+AB+w1bfVrxVQG44IfK57a+tQDjRwTuAZy9xX2Z+8weU7mHzE9V0DRnUsfNR+7L2Nv6e+aNSQRMM+HSQkJzTVPYwz7svsc91g3XDc3N6M39hCfCFfID4dNgAFnHLsWuG9gMDba3WG5PEkxiT0pNiu+gBk/63H92Wd/eb+6t7q+a3toDGyoq8hPDKMx1p33G3VvMZZtJsUD0mK8dYKXrPohVtyKvIusiCFC0shq8A6jLqIOr26g7pqSxmroJGnHJYcdrArmE6FpOEGGbyXgydUDdAGLPhuXNvfnzKQ0ZAhdvrIbsI4MWj5V/OW2qr6b++VRKt9lO2/Sr+8PIc9kT1UPwRdirAHZ/TFlpIwF7yfmPIndknyTCvdSV4js8mw696wNWTS4sjqyAUlpFut5ID8Ao9OzhuHzyqWlOgmjYQlAlWEB4B5j/CbDp08QLKrrp33gUx1T9UB+iL66Eh5urWV4X6ZXY5Z2lnaFdqN4p4jStCcME+AorC2vEBhVF01uyifvNxz7EPnQeZZ8zjk1xZJ93Cg0Gd1jHQbDV0heQplvLMBj8Fsqs0EU7k0y6L9vP2MgvKGYs+YO2S78olej7+pcUuvxpkHxWaCnpsgv+rr2F+ElnSXdH/+WyLsZCFgS1DgmNhYbhcmnVWTiaSoJ4yY+ReseXlluazCzoJN9UbPigbFl/i7LseOIxSwQo5haxjPBckpyQHJUef62pzNH5UGlSKwMehkDOXAoAuja6bLwx85APy0eZ+9V/0oEgZgKaTjbF/LfihsvPvsJ9AZVlUUFjkcSRvOtUtdQ7EYEReh0t/RTd+FzHxKA1DAZNajY5Pvio9OZUkNpBFieseRzk4BiLu4XK2ftIJvG2xkqj9XwxknGx91flzJx+ONiSSaJIkkiKRCVM/ViIONhctKQnKEy1v+teQ9yblpXJfnGbup9GpJM9jQmTCIPK7t+/RBykzKQY3Qb9AvUHYo63vck8hDMxo+vmhlLp2gDd7s1vRvqv7cMNh/wonUowmeckWWsZZd+wGj9qN4CZMJJAkBCSBqdGoMddSJGUG7rgbJNtU23TbFl4i7+AapsXg9icpOy666ZiuzOtkVlBXzFfYVtBVhvcIKfW/1h/zzsvOiCSrgd6D8oauNig14M0dCiDpHOMcsJz5nTxBLqBhQBJy6Z3rwB98ygp2mbxhsgZ02icWpqdU6NUuy1XbG9Z2HAIJO4ZuXWYfMJYJqv2obYwqASWuqIJKfVas/KOtso39tGPjLJ+eRH2KxWdxR7fuo6X+8V3COeOYGuomuy4QaQh/fgx59UEYQfnzxx76y6nkONnFdN52erognlj5ue0IzzZfZtXYrf2IeRZHrKtA1/+tPp8e4QrFCycfAx/gsp876bNQXH5vgnKItR5+ePIGovzrswb+dc3Djsp98w7LpYcq8ftuk46nOy+hH/5WxIPL7oK1UGYWBWtUTgvZB4KDVIGukdkjP8KRNGpgOpAtyBLXW8C8+nT/yHd5GqeTHia7I8SmeVEZr0TAcMSgklycTJcskFSf5JKskUWyRdhl3/exK9NcIUPAfD+B5CoQAFx8zIMgmXSZB3bmBO4FugfzdgMDyN+4nkmuBAx8wJN1EJ0gHCgON/7D74PuAPAedduNZ9zJDgR8Pn4xgX+BQkBBQ8HG+4f0l/kvwg8c0sGc2WAV2Ed4R5YnbVEVUq2c0WOETDyzh50D0H/CqONh5rGMpl4qPefAz5vpy5cdsd75+hAAMLPPTQok5UnhzKO/knRmbCGkXMBMf9XdcLzovn96zDiNIBjYGAgZJzVlr43hlBdUFv2p/9Qql0Cb3lttRC7P2/aZyawdcTffONbLjWc0mFZ9riH4I1cKRDZs28+StLLI4cbuj8kPKViyeIfDkrmhe8RQ2kkydRT5x96PvjDZWri5YmgbNER1P3mm/CAakdykvzTSfBClDoG/vt4/gLZEgKG3Qz5KF4QN1z4i1Hw5rzYdhk0GHPbU7VfRuZ7BqQq3EsS2wTg5OBzsjew81ececDgLoDmggDYoj9ycHGpimlKYojFlYX2L7mLO2TSmWJNZnMth9ZxZyBw0EudM4qOeWN+AmOxYqaAMOBZLYKFcYbP2wsuvzmPrI6eOi7nSZpX5T9kR8HCQkTe0/QCqVj7y+N1q+roDO2cWIwM+iVTNM7Egs1A2S3pk6bOoGhk29X8kz0Qb4ZSwuBKya6tSKk/vEyIJSEpMzk8u8UKfGRklpLpXaa3qMPrISkhP/8ETudnmSKR55eQdmk2YnF3qhztrN1bnPNnocb24QY7vrMxXZ8Tla3f1xRsPUZ4qPZK6GhhImu740QnBjcQYZdxDMPPm81zHRwlZHhFTTA2Se6eqKX0/jbGhnfZacONHS1tdfzJ5ejCpBlR734Dj9x5M2ag0qjqmubMGjj8OO1eXyOELtKR+9ujZOr7UZAo/ih+7l8cfQv7ddJ/mUYaFFgTdyqz04Nv6hxHVbbM6mVscu3h+bZKgrx1XL07zq0IdK9Z0uFfYhGieWURMBq+OKqxectcRkUInRwGee4gWiICC4/zl268ZOWWPov+3jkjrO+Oq8HH68Zdjvw9e2wj4z9/ivisV53YjLx5P9paLTfvMUrXCdF0RhkDU7gWWLpy0xxiULsDsO1rj4YpLDGBsVVKORvtzoiws9nfu9hR2w3Ha/3xFlcj+Svg/0D0o0DRDxy/TSu+Be0sseDzzsu9uvYN0UxQsSw6v+vXk+uIMXJI4XZEiV4UvzKuY3VfahFqK8JcPEDa3hPgoKfJP/+M031c/2Nj2f2/f0ZGEDBrbzOafaePkL2kVa3pehiTwZdDa7ylWCs7viMnZF8OssJsMzStH1WbJVGWgd7yKVXLwyCVSBu2dE2s8iETGB5VIrGQGV2UO8xToNWYhdC26/ztLaNbbeH84uuUhvPkmgF1VcNNgGu66+2NSygF8Xjc9veP08rGsGDuMSnCe7lcGu4X5+22ae9z+3YqeZq8zXQjqFidcpd8VZL/HQo05912iFny+LM55e6SnL8y18nI9afdhZO5epdNVbXvfyM/clnMGdnWaLlR1c8wRKogd81VJeYtncvvZ+9lWATUFIX3en2GB1+vf7qWhXt7S2cWej5zg8c1hxlbbod/ZXfVoQHNmxdpCX86SI7g5ZxRW69hM84xsco2Kugu8Ok3YNUVPpnlcjYNZGRLMhm9Pvvf3vpwqgC+Lbp69/Ydi/KWwv1KMSTJAPM44MtHH4OEa3cGxgmHzJvthNdJ+b5Sh2yMXHuAiP5852ytNIsLG2omnWmrg00aoQ2Uit1I17OBmlr2I7meMg19Hxcp0OCsfxnqRvSatRKlz+vsbU9eIffDSih8P6WlGm3Xm77Vhy4g9YiL46LlXRdi2nYImbwL88BLkfa0KNSPq8J+feC/iv7jFl7mc+kcYtvh1Od4NXvjfjaehkXVa97P5WC9DOWufuMFkoyX3W02m7005hlIwEoaEEJpQRj8WnGcCHBLRS/q43PRjv3FLJ1Lnxn83Yna0bNCC7MG76aHhMPa1z/o0r+SEpUviWQwy81PF3/ehEGdTpt1RpRn9drDI9BdZr6LCAvdKgF/mUcUaP0SeWWQ/9fxkxtR5fX6UDCjSHeUHyMRm39ylwXG4f5QrzyByVXbcV/ksXop5lW5EjWKQhsxOzGIs2OtkEXKBMPtBLh3kvmA234uoXS6C0j3TBj2AXlTU95O0GByur/r337p8Mf3SHp4hj012kbnvygWZ/KLsZt04kqzUAmg8DLmTGQpjPcpojNffkcxnHaGlM+7dmBJMuzZ4IsQCfOZ6Q/K/C/I0i6u3O698vDNqcbqHL2F2O3DhqQR29z34vasNez3GtvcOxrLwzxB67V6ewbnpKc+LcoaqPImXP+7/GL9HK2wWY2j0bH1N64dAvA9LbAaOog+bdBxnvmxxg5rcmKJnIkolic4DLzs/FzHnhlT2bZ7BUdqgeF8rH8e9mm5bu+nGgXHaMhJP46iislBiHOs/5WqNL7fkTZQ5d0CXk6HTz43ljMZOHp1n4/flXf9N5FGSLsH4OaPQxfRu4ZElSNNZaHsX1jqpCq2RQ59UnPFhIf2ChAJQN0mEx0TDvdmavdxqpajR5qzkpO5uS8Hxk16ENa36QEUEsUyhw6YTkdP1jf00dNnHi17rzVs6h3MZH3U6zRY6Vw5yK/S6JXf3OX/dZ8NbFcMEJQUZ+LtitINjVFo65V4e+a3YVmlKmNwuAUryLDHCdVa0QqJBVET+fjFYHWBq8xIHcmPdMtwLbUxbW3w+na5Fh0RX42V+raVAAJzhL7VHDPArEge76oBNS4WoH0Wlri22fXGSSKmzWtZva+/Snvx1yPmRNvB/sKu3GL78fluCbExZxb7xLJ/DeBIyW/QRndiba47y9vG3T89xY55Ihq3XdE/NOr7O/u302+Lh2jIdBAZeP2SP+BkkGhW33uWaLSSpBa+zl6s5J/KgQfyf7Cx4h7lg94YBxgA7cu3K2m98x67BhDm9Jo1i/krZzRheHtHMAdOQx8rS5O41vFDBfRJ2Ke/ZusxbT8vb8WPheHgi4cz71yW+A//o1xjh9n5M6oYoe4F8k4f3xXotRP4U4dIhj4KrEYfQmcPJqLG5YW4NQybjKvDwcAIt3JMM1HGv84dCsQNg5Yb8sOreVTzOA1flym31SJRXUPSHx7R/6Vpz2bCTXDVfObaGdvlMT+Gpnzp09dNKRqN9srs4aDZwTH1vbX+9Rl+A119Da/9vCNA/1Nx1/RaUsb9jTrHCDz5rAZLbIQMJOhV79B0t/UpY3n92WruiXtS9DNoOKJgdlqW7EEE+ii/bCHffrjlc0j4b6IX/Bvme2BerOq9X5wrOPtC7vA6fHXtYhY/2ZMuEk23YncOqjPCkrJJvrYxCC7rIKHUF4a/f2EDKoleAS/+Eq33FxbKX0CwtIyZ4ZiHi2fzl6N/kMuJlymRNoZW43Ya3v1E5Lv+8yurtu7pMJZCZg32p4kOzreX8NOKMJrIbULM1ZKZba/wFs1TXuOXEH3s2dw17fdj0x3AzkMzOKIL4chMk5fywdjUpLCgsZ3V7aoAo46Ch7RD57j9Ois5Dwd1pfFKHHge91fxTkvcgrfIWckkOY0cHKp5tKutfnvjOpFGJxoJQHqNPZqiu03UAALetCl88SfMRRlvr0uekZpUZJj6iJAKMzFSfk6dGMCNtvaoFmcsI5zqnDNmQ5Chcoj1gJ64neJW/rXxjV/eZSuvbdD6Zd7WEKRRmsrDDqhhqh1lpmThEg3vEbW+K3xO/fYX5jOL1OwR1TnVApSnN195vZ4sK3MITTufSlI5l0KvlWsAxsl0i2l4idzDSfzcEfsLXK1tr6UaTp+Ssy
*/