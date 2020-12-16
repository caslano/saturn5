// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_IS_ITERATOR_RANGE_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_IS_ITERATOR_RANGE_HPP_INCLUDED       
 
#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/iostreams/detail/bool_trait_def.hpp>

// Must come last.
#include <boost/iostreams/detail/config/disable_warnings.hpp>

namespace boost { 

// We avoid dependence on Boost.Range by using a forward declaration.
template<typename Iterator>
class iterator_range;
    
namespace iostreams {

BOOST_IOSTREAMS_BOOL_TRAIT_DEF(is_iterator_range, boost::iterator_range, 1)

} // End namespace iostreams.

} // End namespace boost.

#include <boost/iostreams/detail/config/enable_warnings.hpp>

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_IS_ITERATOR_RANGE_HPP_INCLUDED

/* is_iterator_range.hpp
n6a7CjJB071Z0323tsvfwobwHtgB3gs7wQc0H/fDXnAb7KvuR+Da0NwPME+vk4is0uts1+vs1PJ5RMtnt8b7lJbP89rPH9Vyehb20fP+ep6lemPhY3CCuk/W86l6Plf1jsCVoTkMcIOmr4bLdmo2ej6Yo+WQC5vC2ZquOZqePDgJLtL+dAGcCYthLlyg/SofXgELtD6K4M2wWNNDQvSbPPWh/bmhtHsOtYvlg3+ESfAx2ADugRnwedgDfgJ7widgX7gbDoZ74Ti4D47X8zP0PAe+Cs+Fr8Fidb8C/gXeAt+Bm+C7cDM8AO/S8616vhO+B5/TdOyBH8F39fwA/Cv8CL4FfeSzBMZD/KUchoe+6cKuWi/yXlPL4bi2m29hHfgdTIcBX7Bd+mGGnGt7D30zBQM92nt/HV8GwQQ4BDaEw2AHOFLLdwzsCkdruZ4GB6j7EVhivv1R9nqdelKOwSNJr5MCq8NU2Aj2gF1gb9gN9oHdYVvYG7aDo2EHOAamaz320XpsDyer+zR1Pwt2hgUa7/nqvgjWhxfCBvAy2FDrtwm8GzaFv9dwj2q4XbCF5nNy6Psa7OXxu3aN1s8qWBNeBxvDn8FW8AbYGq6G3eG1sKe4qz1U842KNGn8cQh1IMc2XZ/4AKwNH4Rp8CHYGG7XdG4MfcOByzUel/1Xscdrw2rQcU+A9WEy7ALrwO6wGcyENWBfWBP2h7XgUFgPjodpcBKsDwtgQ7hIw18Am8AlsClcJu46DoW+g8DzPMahsdpuJsBEeIbLfl9HOAd2hnkue7V94TQ4Cs6CY9V/HJyk7WMyPFf989X/CFwa+qYA12h6qiNFmp4LtX4v0v53sdbnJbAfvBQOhCv1PmMZHAqX633GlbBA/QvhFfAadf+5uGs7s/VdvX5X2A/bIKNtne+o5VIAq8Ei2BQugm3gBTATLtb+Q9lL/VwIz4Zb4Qx4LzxH7aDmwWXwPHiZ9pfL4cXwSngtvAreBK+Gv4XXav/4Hdyt8T0JV8Pn4Rr4F3gD/BzeBAN2UL8KdPSrwnWwFrwZNoS3wFPhr2B/1R+i+kPhb+BpcBM8E94B81Rvoerlw7vhSrgVXqPuev/I+29z/3LC/WNL7R9tYGPYFjaD7WAL2AGeCjvCTjAddoOd4ADYBQ6C3eBo2B1mwUztJz1gNuwFz4F94Vw4FC6EI+HFcDRcDk+Dl8Fh8Ao9N/YT9f15HJIZYbexp9t+ooeel33HvS691Sex21gSo97hGPWs3kaP57BwvXdceokx6jXx0POy25heht7+n3j99/7P/n1rwPdd57cOItHWggf+wd6ZwFdRnAF83xHOACGEEO4QjnAbEAUVMXIKCgSICoISIEGwAWISEO+AiKigUbFixTZVrNRSixYVFW1aUbFqS6tV2toa60UrrVFRqaL2v/O+N9m3b/blvYT6a3+/PP34Z3e/neOb2dmZ2Tlqj8188JzayDnh1R8FreSbA1FzwzNvDhzT+eHzagnbaVzHXfM8cXRuDvzX5opvrHXOF+fazYFjNmd8R21888ZTHj92c8d33Bz41uaP72POeC2SNpf1CZFCZAOyDdmH1CJp85hfjhQgFchWpBp5Bwmen2T1QcYjhUgFsh3Zj9QiaRewriEyD7kC2XpB0xz1pl/Tr+lX/+9bm/9fuGJp+TFa/29lhqXHbh6V9f9+ae+5Ap+Cfe158M2p+xjn5DIW1YqcN+0c/1eh7tvh60+taSXSVu0fH3YvS3+/knN6XNxKS+ZahLY81vfdqnR+oPbqPj9DzX9g73PHmHl1fZXvNGJm62QGVe2MTajr5j7MbmHrpKAxXu1bK+PH+KmxW3rORZVya5OvJaE7B7H1/tk=
*/