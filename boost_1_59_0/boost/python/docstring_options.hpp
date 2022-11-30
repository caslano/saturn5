// Copyright Ralf W. Grosse-Kunstleve 2006.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef DOCSTRING_OPTIONS_RWGK20060111_HPP
# define DOCSTRING_OPTIONS_RWGK20060111_HPP

#include <boost/python/object/function.hpp>

namespace boost { namespace python {

// Note: the static data members are defined in object/function.cpp

class BOOST_PYTHON_DECL docstring_options : boost::noncopyable
{
  public:
      docstring_options(bool show_all=true)
      {
          previous_show_user_defined_ = show_user_defined_;
          previous_show_py_signatures_ = show_py_signatures_;
          previous_show_cpp_signatures_ = show_cpp_signatures_;
          show_user_defined_ = show_all;
          show_cpp_signatures_ = show_all;
          show_py_signatures_ = show_all;
      }

      docstring_options(bool show_user_defined, bool show_signatures)
      {
          previous_show_user_defined_ = show_user_defined_;
          previous_show_cpp_signatures_ = show_cpp_signatures_;
          previous_show_py_signatures_ = show_py_signatures_;
          show_user_defined_ = show_user_defined;
          show_cpp_signatures_ = show_signatures;
          show_py_signatures_ = show_signatures;
      }

      docstring_options(bool show_user_defined, bool show_py_signatures, bool show_cpp_signatures)
      {
          previous_show_user_defined_ = show_user_defined_;
          previous_show_cpp_signatures_ = show_cpp_signatures_;
          previous_show_py_signatures_ = show_py_signatures_;
          show_user_defined_ = show_user_defined;
          show_cpp_signatures_ = show_cpp_signatures;
          show_py_signatures_ = show_py_signatures;
      }

      ~docstring_options()
      {
          show_user_defined_ = previous_show_user_defined_;
          show_cpp_signatures_ = previous_show_cpp_signatures_;
          show_py_signatures_ = previous_show_py_signatures_;
      }

      void
      disable_user_defined() { show_user_defined_ = false; }

      void
      enable_user_defined() { show_user_defined_ = true; }

      void
      disable_py_signatures() 
      {
        show_py_signatures_ = false; 
      }

      void
      enable_py_signatures() 
      {
        show_py_signatures_ = true; 
      }

      void
      disable_cpp_signatures() 
      {
        show_cpp_signatures_ = false; 
      }

      void
      enable_cpp_signatures() 
      {
        show_cpp_signatures_ = true; 
      }

      void
      disable_signatures() 
      {
        show_cpp_signatures_ = false; 
        show_py_signatures_ = false; 
      }

      void
      enable_signatures() 
      {
        show_cpp_signatures_ = true; 
        show_py_signatures_ = true; 
      }

      void
      disable_all()
      {
        show_user_defined_ = false;
        show_cpp_signatures_ = false;
        show_py_signatures_ = false;
      }

      void
      enable_all()
      {
        show_user_defined_ = true;
        show_cpp_signatures_ = true;
        show_py_signatures_ = true;
      }

      friend struct objects::function;

  private:
      static volatile bool show_user_defined_;
      static volatile bool show_cpp_signatures_;
      static volatile bool show_py_signatures_;
      bool previous_show_user_defined_;
      bool previous_show_cpp_signatures_;
      bool previous_show_py_signatures_;
};

}} // namespace boost::python

#endif // DOCSTRING_OPTIONS_RWGK20060111_HPP

/* docstring_options.hpp
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
*/