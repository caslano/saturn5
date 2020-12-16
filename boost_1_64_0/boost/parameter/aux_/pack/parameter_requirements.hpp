// Copyright Daniel Wallin, David Abrahams 2005.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PACK_PARAMETER_REQUIREMENTS_HPP
#define BOOST_PARAMETER_AUX_PACK_PARAMETER_REQUIREMENTS_HPP

namespace boost { namespace parameter { namespace aux {

    // Used to pass static information about parameter requirements through
    // the satisfies() overload set (below).  The matched function is never
    // invoked, but its type indicates whether a parameter matches at
    // compile-time.
    template <typename Keyword, typename Predicate, typename HasDefault>
    struct parameter_requirements
    {
        typedef Keyword keyword;
        typedef Predicate predicate;
        typedef HasDefault has_default;
    };
}}} // namespace boost::parameter::aux

#endif  // include guard


/* parameter_requirements.hpp
SLah8vLXbrHn2d35ajqCVQ5t7BYig9tI6z3xqxb0nGVk9pJu3+b4/aB2vTak4YYdZcrZVGTSzorHJVWv/Q+Jfza7teI8Z0fo/lWNV0/iJYpclkXIpQtySZJ4R6fK9dEluXvvLAnXXPUe8pfYb7BXk/sWq7p3r7cp43tSnuP59t7VyKqn5F+dMLSJiPz3kLYpc3aOuw3a6Hf5WcJ+aFe3Vmu5wjJqJ+1uuNw1eZOLsmQ7nbTT9eTh+D1s/AomWuq3MmKvYU6hV04/S9mTPbIfbfbSVpVrKFa72warmTMsxpj9yq9LfdcJfGD1iq5XxqLz5N68lvbUj3gjME78fEyB6lLOVzOqln+YQnWrjxmDGYcpxuR79u8W+u/f7UMwyny07FGsI/c+uow/sHRPY0ext9hmHXBvr/Rf2l+wh1dkTl3g5tYF7iLvh9Vd6yGiv+uZqP2dpWv+MdMR+EYWy3vPYRo7QVLNGl44Dp1RB9a1QHyPPpWD1wEb3tOfVk3POiSxBNgAOv1y5sduOXMLRuYVMyhno9gqF+1FORyAWGz569xpKfHS7QH8fzXmSwz3J/lrmuTUxnqO9bMp3uvCL7rPHp2XV+SrP8KETTX7PPNzs0uynZ3XRpfp6RLmaas1VzscE77HapZauufdtO9c772yVuIlG/2U34k9Q/XFmbywh67pVPH/3ug7eVPb+mjlLOfsL/5+Se1v16q4XoeItqly0fFW9bVJmSJ1liXpvibVa3wM/x1G+5tX6tbriAL06Dn/FxTnZ9FNldGjpLJcKHG62qfz/20iVX89SqRt6mVtKI28sao7zJyz9QnuMcZd4pdbrxBho3U++upgIFxMvXpp8Hgpz2xG4mBonHEiec5CqAu/kjRK5Syq0ZgTqOuauE907pNUxntPnT9SW/7GPdSPXZUWqvu3MOelhvxe8WkDSeXU7bFW7Eau/nqQcEuJ1EFpnsEHJGu78Oi12Z5O2E9Nu/C0iAP3R8Qz8k3ev94owpa/fjWs0a81W+R48Look1MOrIvS6JtWGfXWvruX9t1FlMmrE1w7RtnkXR49OUVR10RfQFvYb/99amzdhHpmbS3V6UOCjWAWfINGu9Etq1F+4A40EWWVvmwj49nnEmdgoHH43Dexj+aJ70HrPb5w/8KX8nr26b7XRn5ROlpGj8FZ0n6RtL8W/zPNuXifiP3UwMVWhr8+2zJtBY28/m2FsD73uOb9KnnvFf/jA9JXiH+O+D2F327xOyUQcY6YXv9TO0J9f2MdC3pvd+ybeeJuiPzPtW+163AeX1V5/ttEWi3FPy3wDm5uXzKmi/es0j8kvyMDrn9xB6/+mQRJo7X4b28o/ua8nPfkGU+f/zz32S7c3fKPNvo5tuu1OeXbTJhQ+X+xnTKfQxskP/qskPk7lh5QxyrXaL/1UW38otwwPJeZPs205b4VeEarvfPAz2TSj9GeyvR32iZwE9kgL9yQl7rt0mc0ve8jnnv21tZ1pmTeEr4GW+BWutPcN7GUGXnvHTOO/C7x1tvHWjX97g/Sjb4/nJMKXN1qwc8ct7V2NyTmdz8QP3q8kza8hmusSlwn73C7/UXC1vG7V0jHtw/2HTs1bPS4aN7DUyTf5fbhVq3oe888O6RKmLvtVsQ61mpnF9qNpNyrKHe6+D1ku23X1RWU87nj1yDi3WZ4VLtfj7uOxfq8Fbv9GvfIcdi8Vwwqd5vdXxuVOpUwSe74669nS98hJoTaMWHMu4ZnnEqq9Rltur2sTSrOLiyJHKfi6oQKeZOOUzeG9dJ+4bZhhvISHdB5dmdIL8c4RXxT71+lGJm7OpbFfzb3jS1n9+7jvlmXRs1jgl0SAsHU6u0SAknBGkk=
*/