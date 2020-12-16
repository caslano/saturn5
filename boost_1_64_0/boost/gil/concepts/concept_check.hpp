//
// Copyright 2005-2007 Adobe Systems Incorporated
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_CONCEPTS_CONCEPTS_CHECK_HPP
#define BOOST_GIL_CONCEPTS_CONCEPTS_CHECK_HPP

#include <boost/config.hpp>

#if defined(BOOST_CLANG)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunknown-pragmas"
#pragma clang diagnostic ignored "-Wconversion"
#pragma clang diagnostic ignored "-Wfloat-equal"
#pragma clang diagnostic ignored "-Wuninitialized"
#endif

#if defined(BOOST_GCC) && (BOOST_GCC >= 40900)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
#pragma GCC diagnostic ignored "-Wfloat-equal"
#pragma GCC diagnostic ignored "-Wuninitialized"
#endif

#include <boost/concept_check.hpp>

#if defined(BOOST_CLANG)
#pragma clang diagnostic pop
#endif

#if defined(BOOST_GCC) && (BOOST_GCC >= 40900)
#pragma GCC diagnostic pop
#endif

// TODO: Document BOOST_GIL_USE_CONCEPT_CHECK here

namespace boost { namespace gil {

// TODO: What is BOOST_GIL_CLASS_REQUIRE for; Why not use BOOST_CLASS_REQUIRE?
// TODO: What is gil_function_requires for; Why not function_requires?

#ifdef BOOST_GIL_USE_CONCEPT_CHECK
    #define BOOST_GIL_CLASS_REQUIRE(type_var, ns, concept) \
        BOOST_CLASS_REQUIRE(type_var, ns, concept);

    template <typename Concept>
    void gil_function_requires() { function_requires<Concept>(); }
#else
    #define BOOST_GIL_CLASS_REQUIRE(type_var, ns, concept)

    template <typename C>
    void gil_function_requires() {}
#endif

}} // namespace boost::gil:

#endif

/* concept_check.hpp
6VhU/agjW7Jhgs8xPIpfrquTDh7rfGkkZ2JjUJnqyBq5Vzfjam1/ekrYBKLKSOukaM/keXPw5BqrLZJH/ZW8NU14ejOE/Qz3pyxefyoYNanHNuDB6Mv2b+GuN30vLDOn/bsvPMg8HpUy3dcihC35SDQPJSbGmkgO1Eep00RybBvR4cb0szS5HxQpJ2iZWMUw3Seb8yhr1ukL6aBrBysmcXbsQDTPrJzIOxTNM1MyeSdE2uj9WUcreSeFPNtLtIo65J1y5LnepNn+F0XxwgUgy25FJM+aM2+IjNOPD8LEXRwRp8ML958i4wttV+2rHLwi6kn2x2geM0hbWCSP9UTeEZl2evimOKYf9+4jeOFcd8iSQ2/imI3pHswjtyWSW92vqTJ9mUgu+zrPzsxG8qLHkGPRaeXYYI0h0VyODxeZtS3jd3lWvqqU2xrJ53hBvTFaLscMniFryqPaPcazAU25VnlVaT+Sa8CBARj/eaBhmDa2pQ5HXXkZL9cNk2ul1kaepkxxLnBkKXusOTsLODyj6PDU5oZzZvJKrjVikqsv1OmIqSO32BysWQJGcDaF56IycszK92TzaZ3E+rjZesb5GrEXu8LlBxrLVlO+jTiUBVecyl5gjeP6eKkbTj9lA/2b47DkJIPnpErgTPumyTBPN9g8rcnDLqmDaHsFz13EV7l8P804EL+/pPeqK9TpG7g8STleDVYVHHOLi6O5e6cm1RbJ5aZMTzak155njy93cZgjJkqWrpax4+oZKGwvqthklk18x0QdpbD34af/cXuJn2jErXMKRyzcWdGhHngm1+ahDkI9ubjKwlRKOzs2byvBoBfuLzVyNnZg83/j1o7Q1rbS5rh5Ob7CwXVeTBqPLZW4Xe5HrbD62Ine1aVNQuzdY+u+WMhlk7swEiV4qT24FPRQE9/8fFgxcNkKv+YKPcHRJeGj9Oi84Tfqo8XekAlzZAFhVK+U5+YPNw/Dc2XUY+fk2mV6i8VlDpVAtuWzLkccNtQHnFge3vLmXB48CsIM0TYSLT9IKM9sgbda8AZ24cZG6cryOGYVYTeALwSXg/F6AnugIefkoigOKGLtmml1OdZZQqZpdwMP83yQqDLH/kYOirdR1s5GHp5l8dNVph25JYozsk9ydi6N4gRzOufdCDm6LFnvIDgcfZrdTz6WkdDiOLYy7Q5Xz2/cf2vkqWomkWe8Gura1l22NcpBQVEMebvduqbDZHsterax3cCb2j5MIZipxdnU9sZ4hzID6URKHwrRT+SM047WlD8zobk8V9+6pBl3amaiNAk/hiF3TVO5agc3SAbt7IubcRVNVabQe+bkOmOHbGeFfLd2reC/sce2uNzhYI9qZryiSpVx7nY5VU1CCzInWnjeyYqzv1i6Ene2RP8fc/G9tLFyLV2L4GglZJprVtk/3BeOUL+GV3N47mtJjHORzeOoLWSNtUZwkDb6JjJpi5Dlnk8bE3MlHKGjVeB0Y506B3x92nh/OrgFwP61pBGHnnRFcMhDnKGKRfOkLfdkBAfJNe9Y820scvKlGYxo4Z05G1PjsHqsOGwTKywcZzwC1cfIPm2HV9kcpr5ih9XPQ4g7KVbYwC/1npFNWzq3qiN7+/DiBHZjUIeGf2Y+/qaOixXfpO2wFX9QLMB4z19g/kRAXc7CArsM7UAWZo13Ndqu7XiHJ3CRdkLs8806eBUEiR8Q4zNfV5XhbZznI3k2yMFxKNFY2Wo8J9Jic+oTKMKJ6T3yfN5hIce9IW2tExyee5sZlIup5zpc3oqWeobF4Y1ui3PK4dCQKDjHHA5vlAvOoVaHg+N7vq8HWd5iTOCrtmI8aFvi4IESxjGxw0kHb3KLOFodjj4=
*/