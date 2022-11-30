// Copyright (C) 2000 Stephen Cleary
// Copyright (C) 2008 Ion Gaztanaga
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org for updates, documentation, and revision history.
//
// This file is a modified file from Boost.Pool

//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2007-2013. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_DETAIL_SINGLETON_DETAIL_HPP
#define BOOST_CONTAINER_DETAIL_SINGLETON_DETAIL_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/container/detail/config_begin.hpp>
#include <boost/container/detail/workaround.hpp>

//
// The following helper classes are placeholders for a generic "singleton"
//  class.  The classes below support usage of singletons, including use in
//  program startup/shutdown code, AS LONG AS there is only one thread
//  running before main() begins, and only one thread running after main()
//  exits.
//
// This class is also limited in that it can only provide singleton usage for
//  classes with default constructors.
//

// The design of this class is somewhat twisted, but can be followed by the
//  calling inheritance.  Let us assume that there is some user code that
//  calls "singleton_default<T>::instance()".  The following (convoluted)
//  sequence ensures that the same function will be called before main():
//    instance() contains a call to create_object.do_nothing()
//    Thus, object_creator is implicitly instantiated, and create_object
//      must exist.
//    Since create_object is a static member, its constructor must be
//      called before main().
//    The constructor contains a call to instance(), thus ensuring that
//      instance() will be called before main().
//    The first time instance() is called (i.e., before main()) is the
//      latest point in program execution where the object of type T
//      can be created.
//    Thus, any call to instance() will auto-magically result in a call to
//      instance() before main(), unless already present.
//  Furthermore, since the instance() function contains the object, instead
//  of the singleton_default class containing a static instance of the
//  object, that object is guaranteed to be constructed (at the latest) in
//  the first call to instance().  This permits calls to instance() from
//  static code, even if that code is called before the file-scope objects
//  in this file have been initialized.

namespace boost {
namespace container {
namespace dtl {

// T must be: no-throw default constructible and no-throw destructible
template <typename T>
struct singleton_default
{
  private:
    struct object_creator
    {
      // This constructor does nothing more than ensure that instance()
      //  is called before main() begins, thus creating the static
      //  T object before multithreading race issues can come up.
      object_creator() { singleton_default<T>::instance(); }
      inline void do_nothing() const { }
    };
    static object_creator create_object;

    singleton_default();

  public:
    typedef T object_type;

    // If, at any point (in user code), singleton_default<T>::instance()
    //  is called, then the following function is instantiated.
    static object_type & instance()
    {
      // This is the object that we return a reference to.
      // It is guaranteed to be created before main() begins because of
      //  the next line.
      static object_type obj;

      // The following line does nothing else than force the instantiation
      //  of singleton_default<T>::create_object, whose constructor is
      //  called before main() begins.
      create_object.do_nothing();

      return obj;
    }
};
template <typename T>
typename singleton_default<T>::object_creator
singleton_default<T>::create_object;

} // namespace dtl
} // namespace container
} // namespace boost

#include <boost/container/detail/config_end.hpp>

#endif   //BOOST_CONTAINER_DETAIL_SINGLETON_DETAIL_HPP

/* singleton.hpp
cGe46AsxyDlAfSGiWTx7gNCqFs248DMcEq2Fha+AGxona2u+VbGGnHyLlA8DSpEyK0L7GgkQZTD5XYDPrfscUdK0dXHZPDQHH0B5nx0ChDWweLWLRJDyAeKagqiYAoY96S1ozggdOUF/CMdw9IJiwZJ3jo66tCFkQYZzHFgYCi6zZi2ItC1HLiFp+k/CsyxSZEjTFPr1+pY0enEqTZGlMM5xti6HjPWU2v+SDRSkzZaFPcX+a576Rh1EkUq5oUu5z7FT27ZLvFn91ivd+QJaaMqyG2kvZK8lJ83gdeG+A+XHS93M/7U0t+nltQZj9sLMuHvw7cEhFvLqzmUPOMGjD0sXVDRTasmHv8g1nzvl7slkh4ChFD/K7cA2vJvAFosFgelpwyaDWEYnHdjDDSsFFwRahvfa2ssobQM/Rh7Ogxi/y80qRe9GIfX/Z3v6r6INfROFNJ6S6FU5qBR+Fokz3Gnrbq6rLc78KXvnnhYWFWVqOsgDAYEoJCNgBGdVbjjy6bGDBKzoqyzvBlnwoI4M/nPSgCloWsadClOVJaF7tnFWRkSiDH5HsR7kgg2hQqAcHSoAJFpBEmSqfDv9bERb8a6JbKN8N/3IyB0CQkFKbBcGMorzgHqmEgn7sF4u9pl6DVsdOpYHtnivMEXVXiliAPTIKEoyLrJ4fRQFWT6x4t9glM1NfrwLtHAO3odjE5XwsBgOA4dVrAV+BQnnN0voA0fCQoiDxPnjmpFraQpzYZaMRXKRIVQYPvtpTFh2C5UxLWYC87yR1K42vzE1dUZdeIXUbV/xCU6/in3Z0Fj2MucXl1uhPntlZnOZKkkdO1CmfXf35Jv3fwedmhkP6s5jgB7pgPhCKd5ep46IoLGiDh4pwqQMjfAf0+8cxsned0g/fXbyUZAWMuIknD8RbP1P5vCY0oVUx25vKkTgcNUbvL56b5sQgHpU5ACSNdg7RbUi5Wd86Ewr5NLKPSxsQGFV/uiTEcyuas1lKtXyxwXJ4tSzgGT2BQ+tKNXI24HyfwNaewquNvdr3U27eUGfBFGj3M6ES2+YpKISl1oHasI/pzVq4BtHhQ+4bFdnXUmDnbNCOB4wJSn5+7vrYnnQih929yZVnH3akoV2UiEYiLrr1ut5sxJzwMD43iQZ+zu8vQRsUoMIBOB7LQoB8Aoy5jmYgIIkEreVI04pchk9SGy5CfBAk2NFrOuziz5/3xilLstcZuuBy3ww2uARl6EybIuMrAEaWdnNIEzChHgMiZ/ZbNdl91j3qiNOn0T6FIPWmDPqHO76BYCm+XH4sFQPIuUUTLnkHwqf6eDYOAXR20cIKwkYbWHl9mCxzI785hAExqCraDGSne+CTQh4yufsPiwr/k+b/AI088nAPpP9O5jymuLgCS9YBL5ffMTVFdutwUdQAo15Pfzqs/1kJhV9B6OUVxCHdg9RASqhOTGVMvvMI+CPfCmBIz/S7oY7QLJP79k9iyEI4eEsY74mJkvMMpZ2GipCSG80eNWW5lR0luuIeWBHVdFF0+kkrMeKIqYN5y1THlOdR47Sf94kxo0VJOz+U4dK4nqXj5rqccPvuttGlNWBArejTA2gzJJJVxP+kcgh9HNOGhTwUFvR/1G5yT+GQMk2KKL+d2EjD52igLOAFW2mOS4fFZMEj3SCauYJJy+VQ5FNRBd9KrYkPxmUnc16j3yKm7blYsvWa5WEWR0zvqmqBc2J/c1LX5XWtMKGnpP5QUdzfbCJ9gqSI0VOZd2D3myTzLbQ3IrgCyxdbAc1nOPaxqzrgdds60PGiyEYKUSQFT/tL8U1aeStK1gMxk64zuVTQNrlYGC7Wz1+cPOdafLenBdJSRPmNYZBJ8NZCp4LBHLK/eHzwFZ+/e1PuoEaa+FmcZ4JNQLhZjfWQrecCfrl/7ThxqO+z8e+A55LyTcsPLoWEDyjNH1TqkFakNgb3HaKYii63pYI0au9/Cj9Xe6SgPHtsC7iP7xX4VIite8WVHjaHnu9uQGzqPSIs3UcZ/0aAkt/usK67VRL+VpN3v0fV/T0JIHoa07K7H+h3VOVc1Q9Nku/nmYJZttvol5XvGtd0RO2O29gj/iRQbngifx2Ubk78Aat2v+psONTxe7E+Tq3y6R7bKPbFkwrZArFD19dLeZDDYBT9NzuufG+ckdpk3v24i+YEWtghhOUAPDFogrWNioFxokKWXAgQm9CTebkjxaYy+Gl5r6axPfpPCydyqKeHR50rnqVtoK7RNN34UTgdxktb5YWzl1aIZMGQ6e70jakx/0nVNt6S8+QjpDXSuozZJKXYowvAIX+0ch+0UjcEgUvFmm3GQ8vGE4v1EgP1YofEYqfGoVf0L6LTilXaOrIhcW/YcI/ZbhbO+oLw+G7tfXThfUzpPgzxdEDxAGIMu37ReibbQ/IQwgotAXYcAK4MAqYaB/wMAhIMwxYwfIzcRJANBhwMBywWwzUuwhiuQhyngl+zv756w/NBHdfQC2wbPFlclwpq0vycexlP36rjw4r1XqytzWsT+8EjXmHoAcLzSkMwQkQDAOdHKEogSahA6slyj+xxWOqQfuzrh2LomqPBbNCwdK+jnNFySI+mJpKQyNKJb1GQQPFXYUy0+XNOYUZ+oVKtrWerBjL1OS7luwOcdKcgBCPM9MoobEXXKVvviljZCoO1mY4/IwGh+fIeH2cOlb1nKvJ9nw+GLBGyP4BNvkfEieNqJkhmCBYMMJmrHOYIPODAwFz1IXFiDfo4cpFzEYgcqMXRG/J/EWwErj/4K2kIG+HCDle8G7Ub65/VH3qm82nACAwvoZ/bB2IwNxElKD2vC8n2ZxrqGdaJJDD6IfiiHUnh2BtePNbCHJy/mCOf1FteMU/pA8sXx/FiMH0GMHhmGOH4Atk8KeAZAI3ZQ5syWh1xfn6f28OqoX3rAHYk9o1bmUCDMCxNh0vlkPa/wROgvDeo3vkJYfudKoQCeAK+WpaU7N7Mw3M1JyQeOsjkQT4/nvFzT31coSJJj7Gpe6TWAIJXBpzHhIZwfcvBOlthx6Rz7lrBNWxJQfzz/pyHVXIRq7FG8Rh+o8YKc86zkDTzrgPQKSm1lSYdN8eNeZRRxDZNWaYNyKXMM7DwxQooF7mxNHkiOFwhhBKiCgJ5uKuYY55DTMbz19hl3ESs5H+xKEAsC+0Uuldg5LEqIlJZz7CnLiZNpws7p1VmXC7nwne136lAmAGadHkAoNGCDETSUlwUb67U1U4HxnmYqkNEBxsWFcCDGmG9x+wRJMIFBUAqgpVMzB1PRVANbbnJquvHNZiHjlfWQh8Rfp7b08DG3fbvcXQO4+E4KpzO6esuiKdF7jOMZ+jOtpAdIr1TtYSe3kwzUO6FjGcOhIIXEkXr3kRJBwAixibRhfiEr1NGWb67tGH7AyOu206cYECF/lWip7TWyXyVuW5WD4y5IvzRb8zbTEgDE2VZZO/gX89EvkyUvkQjDZKGvZKP+Trp5/PW0wjRj4o6hCUVhJ8VA5vswwUbXao/CHfgSKBSxKueULIUCiM8b7zbmlQIXMiznJSiWH5q7B+makTEMZAAwHxMVpgKjE1LGGT4H8hQrztZeYWB5mZNBCIPEyMh+TDfBGgFl2718YHzIM9w3dke/upvm5UhJK0lDQqs+a0yz4UgPy0KfsUMUXUShA0uIf9uXUUSRoUNn4qlaXUF4VK1fzT19BKNrbfzMmlK5wT/O/VxjSwneTS+li1QlrtXX0NgZT1XU1NQsYF3o/KJnC1Czz5RHIdC/m9haxVidAdD18q3rfNipPFTLk1key9ijUdVwpSXw3N/wAbL5hlrvBqNfnyL1RKNa17oGLlYKqqNf27sY6lUcB6T3xYI8Q6QqPZftTUYS0xe8NNMfvlFGC+NN/yWLuZmqsel1lMiPxbNMVeNMmu3am+uFQ1vgAQvCm9OiCMPHExlXF/MyAGtHAVfKslOhjyXLtFPA/MJdtRusPvNHlT1bsXMOUTawWrq3LdmoVyanOrqwVPzXDTtapz2e6w9Yok3YX/WZVYZNQZahXZSsK+ahBHaxZ9p8fnuyI/eBdJZcX/01pMMk9Cz4tn9m2k5Y2OcW6k9VaSUW981ZCJFfUY0nzUtC3E8Y0a1RReyIw385w8zvY8s6fQtpvcxMk9coEORmojMbl81IUOLch0E7zMNbcycLdCNcTuyVQl9LUi7pa/1rTy0dq00bOS9bRya9PfstYacdoE6N7L4zmYWEPABG7OGHnBdew4aWQDTY19twfM0LtOFKDwnWNnqLIpy1+JFfyo3e1t5bITdvw541FdFroOYBIKelq/5FFcZiK7vAAR2td0ldHkGFNx28B3q660HC5y0XIVrg93PRR2EY52u8Vyyyt1A17p/L3EP9HuNEvqAv+vC1vuP2yTrse9arPyWvDC7qyDbD+hz1p55MDetJUgHLJCZr1O+O2KuM2iOPaiuN5uufi8CZFE1aNv+phJ351R4Tn6uR365h361thWbqHygTlks42Cs3l6bEYCFb4+fr4+N76+GJaxYYYxQvaxl528K/Yy3x27SBb9dj5zh53fSaM+VbOxHh/5xYva6BU6Q4lO7zEoizUX77FbH4o+ozVeI3UEltjGjui6CyDR5uvvxCtKMBzJg1dvWTxJK/xxCnzJKQwP3MKmE4wYT3CRGG7DCr8wUAIEpmjd3hhHX0zuUOyCzNBJXXyLGQyraYxPLlhxUSaCVxac3xQoCvEsaDZdTG7N6bjf/3y8Aw2sLb29E/0MNW0NVc0M140MU/QNty0NiY0MK30Mk/wctWwd1cwe1owekvUftiwfiIweKnweEv0uNG0vVM0u1o0uUvQvdGwtz3ygum2VrTdxk4HpDolhsTlzmODB+Blj2hhjthhjfBlj8rmDnAFJzU63VflexDG0CMG1l8zEbLHg+B1pHHDAxMdlwazBXIzQvAxT3w3RHg01wUCC++7vY58xwqpf6LTc4uLSD3/THZFDCssw9gVNg2IywAFPF3lP1jlOh5nFUZhOU9hOdgNPTchOSHnQUbhPUhJOFVTRmjDQnY/Qn6rQYarRYxLQWZ3Rm5jRWfnRjtTRfEXpNL3oNjzpvlHUPwo6jybazOl7jYl7zcnrrEO6vrgd1zsN592MKM0NKRkcKfMNKRPth3McOGecOImcOLuN1qX0SWE8WJMcWDsNSwA8SA0MSygcSd8NOVkdWdE9+FL9aF1xIgNB/yWLIElBVnUbVRsZ2qA7dCfZd1ca2cTb+4w5dWfVKyUPJdRAhOK5Cgd7Cr99hoY/gvGiozBBo/CujgBJ+BptehpFIRS2A1UwO/lwOD22GT0mO3wXGhn904+Isw++HQgAslYqcI2VA6Ab1LfKtK/MtT8a9IQVgQCUq5MZbvgWadsn7A3Nf3UDFsvZCkXeAjTaeE/e7VdYG+ncGnneIMzcIkTUHmxZF1NdI21ZH57YECXeEEXZCknfKiHbIK7cGv7dOu7aAoW46We+nr+8ZhS7BiJ/pYh4WS96IWF7FeF/LUZ5Ae1+eSN7TVGAg8h4Oc6A6/G4rlS9sVC98VPj0G/nmWvhZKjhSTcIznjkbGqiXGmOcybNS6PbbyDnckTh0SzhP7DGTnnAOVW9DQQz83L7EGTdWe8DHzMRZAPR+HW35zdl4XGc+rcpGx2dwxO6xhmJxLMgLevPzCIqDWisnNu3k121APxAJxcoL2uQLLfYLfubn23qmltqm5uKlJO6mb2ylm2jlMuan90skqNCmc0qk+tiktNSkO3GkIN+CXiBMuNlPfNJNQtONhtGNyuOAmBEgY4sja7Ehs6sgO6Ugg4d6F8yHpUyGcVaOgkbUrVE4bwAwV1LwYJvtGjcXeTVXykeUgTwLxRbUEBxySRyZ7l7gBLj7EJyHwvpGYXrAyv1Her+Air1nR47usMlRsQ7yMPle8g56NInKMxThsJZVNpbhsAZutYvqMAvyslFuN5FxtNlCsNH1M5LGBhoe4BhlxFhV8FrV3JF+7omv91aqFt2kBPYKzlpTqKUYesltsWC/oUdEDXpNZz9NSsJIKXai3XTK8a8yW4+TXMdHkoNfrcVL1oAfmQojmwnrnQ9bqIsjv8Zv7oI36YSD9ESj6AGD7ewHrcVIHvpte14rWbIB8fYplBom6/lC91z1ulo1nB+1hmPt+xwNmFn+6eMPmFIZ8qR/vBo9nS/m1KHaJRfb2xFr2Pcy9lU/DFYl/Ne3L7PVKYmL7LDnWoOgajWrM4xX3VH3oZPr/LUUNN4M6typ+J7M2pkqCPj3dOvAjcbFt75/mWj0MS5u5HT9YnwRcbrcQWiWUG7l/7sES4gmGu11N2rlq8lnF+fmOulwt2tRiiuw52tgm+2wUNWIO9yCl/ULK91iod9J7+qfXb1F5yNA/iURSQ7EgW+xp1b//X3E4kno/bc3j81YNDAz+7HTycwQceMBowYUulXDva6/wL43BgR3xBmq18PtnpY6DiuWXREgSp8ahEiYzTqt67fSkplEDORE4JjI+7DhL/7Fxx7KhtPXnD2wcqN4xkfe6qlguW1fDPWRqP6RAtQ9Kmr5+POqf1EnCGILQ9rLDCaCBDZ/Fvau2UBOfxf9atvCBvYeJvVATtAVC/sxej7KFjepCXZ710XRcAhwiTx7MyGu1s3v4Y8StbX3H/vlsWi7jYCK56/d26QLdtjmxYRB2QBffEcnR/oDcaXu+IcCGBh4g1oYvm1vTfVt+Ab8doF9rcH/X7frSBKyS1mKIFxgojFynIR+xjkX1jRz/1tNwS7pK9BRxLj7e+TYKuJ+aFGuUUI/7Fs/lMo4a54qtow+hjUCdPWk2Bemt5t4R/9ygj0DJ1v+O0EGV2dL/6P4V3n5Vcr8B3VEc5wosbY/cfSHJsPdwAE1foFJ1kEwS87tC9/J0C+rN7lczSleAwZF3o0XTfsjaitFliYtBz/RiWlz+QS2QD0o784QrSX00fpd8GTToBAP5H9Q6Vz3+Be62FTHgB/t2/QDXgBFnSPD4c7KlTyKzDInANKe++VfdKut5mm8fY2+Nnd3b8y1QY+ytBQT7QarO64Fr8J95SrwsxKo+5IGRUNKYe94POI+mQc9eiQDVv8NbfF8ZlIZam5DxTxP7T4pbxyF6d6HLeJcCTfSKHSxa9oQhINbToGFHf8BYhDS5wUUZm0C7D/fqsKBqKW0WCWQWZr6pZl6QLbnvab/PCgBj+1KSVkH8245v/ZcMizz0YUZoyUwgsx/xaeqtPKFtoAgXRrguX5Sc0lVI1znSs0CHkSq85QMQ6NA15/EfSrFOK+xCB7DC1+T19F1J3bk5g73KQ9E2JmN+fXhcKK+GFyPZPdzc84pAmny5+fqUtk1fYgn7bJGN/SExbICWqR96MmPBFY/AT+i1Iz5rirubaKVunpJtj6qNwHMvANaxtTUcJuKS9kojVDwAq0nt0UHw8CevskdXT0mOnwOEfgnyEN68uSI9mmH1x6imqRcb1U4vdd5ru35XBR24KVcN/7edtv8MA86BOjeJWZAedBnL1+AI/F6yjt/M9OBCViG4tD/41S03QDIlXQIgrZkv3IBGjdeQHeK7AKIz5gJe6//MzmD0pAoSeb3Do8JFwxxl1A4CPMfWpe8CR2vSJNeL13h3grVib7qA8nPeSsfXimEgxH
*/