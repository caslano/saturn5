// Copyright David Abrahams 2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/python for documentation.

#ifndef PYTHON_DWA2002810_HPP
# define PYTHON_DWA2002810_HPP

# include <boost/python/args.hpp>
# include <boost/python/args_fwd.hpp>
# include <boost/python/back_reference.hpp>
# include <boost/python/bases.hpp>
# include <boost/python/borrowed.hpp>
# include <boost/python/call.hpp>
# include <boost/python/call_method.hpp>
# include <boost/python/class.hpp>
# include <boost/python/copy_const_reference.hpp>
# include <boost/python/copy_non_const_reference.hpp>
# include <boost/python/data_members.hpp>
# include <boost/python/def.hpp>
# include <boost/python/default_call_policies.hpp>
# include <boost/python/dict.hpp>
# include <boost/python/docstring_options.hpp>
# include <boost/python/enum.hpp>
# include <boost/python/errors.hpp>
# include <boost/python/exception_translator.hpp>
# include <boost/python/exec.hpp>
# include <boost/python/extract.hpp>
# include <boost/python/handle.hpp>
# include <boost/python/has_back_reference.hpp>
# include <boost/python/implicit.hpp>
# include <boost/python/init.hpp>
# include <boost/python/import.hpp>
# include <boost/python/instance_holder.hpp>
# include <boost/python/iterator.hpp>
# include <boost/python/list.hpp>
# include <boost/python/long.hpp>
# include <boost/python/lvalue_from_pytype.hpp>
# include <boost/python/make_constructor.hpp>
# include <boost/python/make_function.hpp>
# include <boost/python/manage_new_object.hpp>
# include <boost/python/module.hpp>
# include <boost/python/object.hpp>
# include <boost/python/object_protocol.hpp>
# include <boost/python/object_protocol_core.hpp>
# include <boost/python/opaque_pointer_converter.hpp>
# include <boost/python/operators.hpp>
# include <boost/python/other.hpp>
# include <boost/python/overloads.hpp>
# include <boost/python/pointee.hpp>
# include <boost/python/pure_virtual.hpp>
# include <boost/python/ptr.hpp>
# include <boost/python/raw_function.hpp>
# include <boost/python/reference_existing_object.hpp>
# include <boost/python/register_ptr_to_python.hpp>
# include <boost/python/return_arg.hpp>
# include <boost/python/return_internal_reference.hpp>
# include <boost/python/return_opaque_pointer.hpp>
# include <boost/python/return_value_policy.hpp>
# include <boost/python/scope.hpp>
# include <boost/python/self.hpp>
# include <boost/python/slice.hpp>
# include <boost/python/slice_nil.hpp>
# include <boost/python/stl_iterator.hpp>
# include <boost/python/str.hpp>
# include <boost/python/to_python_converter.hpp>
# include <boost/python/to_python_indirect.hpp>
# include <boost/python/to_python_value.hpp>
# include <boost/python/tuple.hpp>
# include <boost/python/type_id.hpp>
# include <boost/python/with_custodian_and_ward.hpp>

#endif // PYTHON_DWA2002810_HPP

/* python.hpp
ZyAy2w1vX4DMQV6B0i/u8IrDjMzI0TMUOfqOiFwAvsTXiWD/TueABK7TiOwgIjuwE8MjOp1HdiI7dH57rZyJDNgfmPYu871n3tsCzApagkh3FGuR14n60Z3OY7STaeE9FmUNjiM/JO44ThwBAzYpZkCWznajQsNNY0aOaX8JDyy1ZmAqZ1+VuXzeZUvvxCHsEPcvarHHi5lUk3KBQo3Klee3F91Ewec3FtlpOfwOrIQQrA1gzXZ+q73wiRLEVFJEHhBIzU0qc42NpPxWEigB+Y2cShPPY+6AsF9rxl5zByhN62BPwDRihrN8qvODZR8ORb+g+IdZvwl9DCjaDUAPGKGlFbZEFXgaq0FChgPVL5z+5uoPhyqoGcdx+V+vP7sZUD4CrnxpitjaF+cIZm3JGJOyRj0Ic8/kjimIxorH82n90wznAAUG7EU/UePpoogaFQfOZ2HwzxecB393824/x33kiCWgxDQUnBW9GkX47aqFyM2V2SvgRbzfqPoR87MMuK/XlUB45vUBoy7OFjs05qaB6jnm/Pelby64yCWn5vH2GfqAF493x17LNe0nY834/3jMyfU4Jv777b8hxWimiLXkBiLXsmd5A54GvKU2MICDr5FxxSZzxnYgdKvJhB50xst8fMc1ct6I2N+9fs8mM9aMzOf5TXuzJH4JqZ4IRC7G8QgzMrEothOJ1rBQdO+JpSZDvxMyEWwCCkCYnk2CzCaAvBR+YulZY8Ze9IJuLF8K8KxD8R4HEKfhJXIAYR5PHcDYWwgM6fyejaZnI8J1yvNmA62ZqEX5mGjmgjT8UPI1xN1uBMwhfrCWBy5nSDRTbt4wzFMbiNzInZpA5Id3c51r4O8YBYKP0/dzkB4leUCeW+6XmFozcsu9EoEqrQEywD8GouWakR/Wyv2FdWiuZi/jPbWxvzP8cQUTQZ4m1g8gGhFEZSbXfhqVQfVBciRGWbFXvHyIyh+v9WpFUzSW5xlUb6igcF5+zMmw18b+PoQQdwwBoUHvAgSiTkBqiF1vRi4eLv7GWHNG7MUhnm1IMRX14A16QJgEYFPsOiS7EOWASqo1PGsBDxhsVHRG7TCzqwcqaJWY4Il8M9iuF1+BCoHAIAEwR72IJuDAIUBy7c2gLnk09poXYGIv5qKSkRu59CeMsbRG0VGquhNMsZnURABKAom4kMv2Q26hzCZdhMAB5EWKqoCzJLU97CY0CdKC8n8Sk7yIQ71vZXpi6qlDcy8U3w74GlEAYCI1jxZ5npVj8cCT+3vNL2SxkIux6HrsYx/kwnktGuCq4egXRX7jRcg8SJC9n33Zh140AlIC/aqY/d5vvNmtANFyjz0xoGVfoFP2BeKy79iTZzx/YNkX0LIvoGVfIEn2BSD7AvbFBSL76vcj+lYrmffa+7lpENl11ec9hAI/iuz7R+yVPx5Q9s1DUXHZR2FF+ccgLfxU2jxQcB8ZGBeAdZ0ykIIJctC0n4AohBhCD1hFPifD76BIw+Y1ZNgQCUCCV4fYq5BnkvjbEOFpRqopyA9ULkRmwlC5ASYlMzCainiASMn8K8oNJow8cL/wX18Run0DkQcoSpB/gOlBmX+ltABzpcnlOiQDJMQ0IB6hmQgVMd3Xw2oM8Ht2AqCbaetRBu8Ei7xcja4HmQvh4GmltKQEtGFI+Krh9gb22nWIERGcT+HbSoGLJKrb1ovsQNoQ7AWi5w9FTw+IVESvWsvhwC/CwS9S5OJSVBPzOpABBUH6baU8QacvkKGBonDpQtX1IHEtJWJMSCJ7te6Ukn+jHz3+lSGe3bHXhkAiRylM452QA8qyJUoGexrHUCCrLtfE7rpeQsG5kL0Ie4pyOefPTCFpfy6uOsQ=
*/