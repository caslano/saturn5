// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_PARAM_TYPE_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_PARAM_TYPE_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif              

#include <boost/iostreams/traits.hpp>
#include <boost/mpl/if.hpp>

namespace boost { namespace iostreams { namespace detail {

template<typename T>
struct param_type {
    typedef typename mpl::if_<is_std_io<T>, T&, const T&>::type type;
};

} } } // End namespaces detail, iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_PARAM_TYPE_HPP_INCLUDED //-----------//

/* param_type.hpp
xrYU/kobT+aVlyf4vq7tWve+Jg9HrR3wTkb0+3pXRvR6Amvqzh0fPrcqI3qNgb1dG/a+tvOoey8h/f6VPC560n7TbTeVbzeoe8nLrrZblcz5Pk/G/c3hnxvs9Tu6u97H5xSVLl18qSoTp3SxddXiZmXlK0qLvOYy4oZ+P56l7pFnTsrz19T1NdYQtC9EjOt4dDe8j83flNA1r33QL7zGiLqeTynP+wL5CfIW0tVHqxMx9JfjpnHNNd0fuUVdr8aeAasY+ZGsK5jmcCfN5c5uZXns51hj8i51/RTGpwd1P74lazDil3LvJ0rnQasPKXgeshlxt8/s2zr2QA+Xulkpyq1nOcn1BWWOcv/7yq3W1lie4XaGvpZx8mxdmhZiXyJ7mfw9GdrSOj2+9fXsfF/Woy7fd5F8b+ejjpH5SOd/8ktEHk42PBMphmcnzfmN27VmX02WXh9e/QYig+xvdj0ceV19q5NV+/QH0zJlx1Wp9cz571H3HeeM0BqMZfI5Udv9Q6XTWq2xuI1nbzthui3D4kzrIc38ya35hqvXzHiNyPwB+TNi+/9HQ93vfeVeC0e/BfPLHdf/oq63UuV1vN9Miadx/YF1Mk/9PiQgc7rsQe4pPR32W7x0uf7gKfX3q0LfPJcVOp794aF7rNPJPQVWksmeuGt89nXc5vcUW8rz3VsdV1qjqTkUE/JS8/omuGv8rq3rn0PV9fXWBMK2xPKZyhrthqzPqtuRm6G9vtDtkHPyXMW/P59tq47KVt7vguTIb9iRey3KvPccJEl4FXmspmfkmnLmcRhlXvt4cH/8YwFEV/UnbCDP7OgbyuPJzZJatySTt2rGP+1bS71D53P3M6brVv9S7rX3fAa+VNc7ej4Dh9X15qFnIM71nkz7H2ibu8qVN7It9ZuE+JCJyCbOZWa6bL60rGwl6/gt4Akp43W6oNh7Lb++6t5OVop5LT/cNq9jocciZXrvqyL3Gt8dQ9S1TPSCut/wBHXO79mGmK+uN3N/K9HpN05d7y3H4h4liOo76stzky11zFajTOvGKp116Fyh8lB2Mg3AqO8KoeOGr2fosUaHXgvoUP/oNU4vJkwV7jResaicf1m1iWF3lve6cdeq+0Zbafw7yrxunLjt4x7Wosev7YThu9gg0KVZMLl1C8sRZ/camTpt7gnZ+pjYyJnnlwz0KGdc9ogeexRneZOZQHmTWVfe1GKjbgMbWd5k1lPeZNZT3mTGVd5MSbS8CZfxxYNlzpnMAb0Mudkub3pFri/nqL/ENd4rdL/PbRf9zh6prhdgGT/z5Zqby5ZeprJFvgera2cwv7qFevaLSafZg+iDUOs8d9D5+WiqtEFF5wp0tiidZlpncHvZg0F0dgyS/mffIPmc6blWNfoco3+ncnOqdrNTqiVprtdd0Wm6TIW9VYQbaaTDxI640Tw3qtwKH+d2jP/dbxirputi7udv9VBzHqiOyAOG568szrF/9eSF1+PIC9Ux8sK/XHmhBFsWDomRF0RnAzqeeUF0dg+JPy/Y+keHJJYX2mTpvKDdyBz67eeF8BjuTJkEnBXgPmF5lr22mSMv6L0WQg35ePfYxg3PPbbT4FXq+kpT+nOvse2sv9NuUNe/8IfrHpeq4+X0oM7W3xp9fe1zJdSpMnX5/EhvqT9I3+9adfyurwOrGRjXqc4y7huhv+3eoq5/5A+n70Z1nGxexzor8rmwXO+O3SosC3Uf/gp1fMTXh77AO/nGmyrffkPn/f5hVjfjfk8Z8Dbl14f+b9BwfWPQ9Yh1Sudr/weMNhrm2+NrG+FvH2MdL1PZdAY+D5I8LTYkxu5+fr1+urpnKc9rppyrs3t76yWf61ut9itb6cw=
*/