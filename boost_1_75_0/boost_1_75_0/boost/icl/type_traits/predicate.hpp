/*-----------------------------------------------------------------------------+
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_PREDICATE_HPP_JOFA_101102
#define BOOST_ICL_TYPE_TRAITS_PREDICATE_HPP_JOFA_101102

namespace boost{namespace icl
{
    // naming convention
    // predicate: n-ary predicate
    // property:  unary predicate
    // relation:  binary predicate

    // Unary predicates

    template <class Type>
    class property
    {
    public:
        typedef Type argument_type;
        typedef bool result_type;
    };

    template <class Type>
    class member_property : public property<Type>
    {
    public:
        member_property( bool(Type::* pred)()const ): property<Type>(), m_pred(pred){}
        bool operator()(const Type& x)const { return (x.*m_pred)(); }
    private:
        bool(Type::* m_pred)()const;
    } ;

    // Binary predicates: relations

    template <class LeftT, class RightT>
    class relation
    {
    public:
        typedef LeftT first_argument_type;
        typedef RightT second_argument_type;
        typedef bool result_type;
    };


}} // namespace icl boost

#endif


/* predicate.hpp
/lGhBHxhzuaSXISgIdZtOyoS3oz/plYUe7xs42uVjQoci8ZkgVJ08gkSB7qRbfOpLuDLr5tKV/dOd0Q3030qYi+AbBAB/ZsxPiMQFjql6ZGaxSK1mpJcu56Trpu6OuX/URHGtHq9DqauI+sVjSFICKynT0zCXG1yPYDahoriVRXG9vHe8kaFVMEOqN9a8FQEOB+5Z9algeE/tFGkyX3lsa/dpmT2SHVP0Dm/NWCKRxXu5d3P12WnuGGmt7LzL0+5sMf246U7g84+FnqrcM7LJ+6TcP0MwOaut3/hX5dhrXTtbBrM1ronm70kkFx+msCDIgb247sp6hHgudK+ceCzSrfm7NlhfMcpNxJpXAlNv4A6ExQzNI2a0D2US3AODoiDe6BeTg5FNFbuaYGQjWmhwxGNvs/LTuhd6oomiju8M4fqEtp52nNYwRB3pZ15/a8S79QqXYp9Q3DlFdCZQ6aqhsVWtFoM7PgU291TzAkMqpabnVPsYAVGL+c2OwKP2oYTQcuw0HMYWSdqS9rtw5/LFro/c+H9zSrme0I/VvrAdfL+m9Lt9hLRvB1Wf8X6K9q7DX3TvoN244NRzFdoe4Ka7vqh4+SbzqN6e1d7CNfrClDlCETTz9RboYqF4nwAxEfbCLP5/uRWv0hEUceUdF6v+CmLiofDb4vdRLsmEMYpMx/bbiTexFLb9AvYgV7NWqjSxdaqDoT3jFZHZiP7
*/