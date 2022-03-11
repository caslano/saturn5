// ----------------------------------------------------------------------------
// format_implementation.hpp  Implementation of the basic_format class
// ----------------------------------------------------------------------------

//  Copyright Samuel Krempp 2003. Use, modification, and distribution are
//  subject to the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/format for library home page


// ----------------------------------------------------------------------------

#ifndef BOOST_FORMAT_IMPLEMENTATION_HPP
#define BOOST_FORMAT_IMPLEMENTATION_HPP

#include <boost/config.hpp>
#include <boost/throw_exception.hpp>
#include <boost/assert.hpp>
#include <boost/format/format_class.hpp>
#include <algorithm> // std::swap

namespace boost {

// ---  basic_format implementation -----------------------------------------//

    template< class Ch, class Tr, class Alloc>
    basic_format<Ch, Tr, Alloc>:: basic_format(const Ch* s)
        : style_(0), cur_arg_(0), num_args_(0), dumped_(false),
          exceptions_(io::all_error_bits)
    {
        if( s)
            parse( s );
    }

#if !defined(BOOST_NO_STD_LOCALE)
    template< class Ch, class Tr, class Alloc>
    basic_format<Ch, Tr, Alloc>:: basic_format(const Ch* s, const std::locale & loc)
        : style_(0), cur_arg_(0), num_args_(0), dumped_(false),
          exceptions_(io::all_error_bits), loc_(loc)
    {
        if(s) parse( s );
    }

    template< class Ch, class Tr, class Alloc>
    basic_format<Ch, Tr, Alloc>:: basic_format(const string_type& s, const std::locale & loc)
        : style_(0), cur_arg_(0), num_args_(0), dumped_(false),
          exceptions_(io::all_error_bits), loc_(loc)
    {
        parse(s);  
    }
#endif // ! BOOST_NO_STD_LOCALE
    template< class Ch, class Tr, class Alloc>
    io::detail::locale_t basic_format<Ch, Tr, Alloc>:: 
    getloc() const {
        return loc_ ? loc_.get() : io::detail::locale_t(); 
    }

    template< class Ch, class Tr, class Alloc>
    basic_format<Ch, Tr, Alloc>:: basic_format(const string_type& s)
        : style_(0), cur_arg_(0), num_args_(0), dumped_(false),
          exceptions_(io::all_error_bits)
    {
        parse(s);  
    }

    template< class Ch, class Tr, class Alloc> // just don't copy the buf_ member
    basic_format<Ch, Tr, Alloc>:: basic_format(const basic_format& x)
        : items_(x.items_), bound_(x.bound_), style_(x.style_),
          cur_arg_(x.cur_arg_), num_args_(x.num_args_), dumped_(x.dumped_),
          prefix_(x.prefix_), exceptions_(x.exceptions_), loc_(x.loc_)
    {
    }

    template< class Ch, class Tr, class Alloc>  // just don't copy the buf_ member
    basic_format<Ch, Tr, Alloc>& basic_format<Ch, Tr, Alloc>:: 
    operator= (const basic_format& x) {
        if(this == &x)
            return *this;
        (basic_format<Ch, Tr, Alloc>(x)).swap(*this);
        return *this;
    }
    template< class Ch, class Tr, class Alloc>
    void  basic_format<Ch, Tr, Alloc>:: 
    swap (basic_format & x) {
        std::swap(exceptions_, x.exceptions_);
        std::swap(style_, x.style_); 
        std::swap(cur_arg_, x.cur_arg_); 
        std::swap(num_args_, x.num_args_);
        std::swap(dumped_, x.dumped_);

        items_.swap(x.items_);
        prefix_.swap(x.prefix_);
        bound_.swap(x.bound_);
    }

    template< class Ch, class Tr, class Alloc>
    unsigned char basic_format<Ch,Tr, Alloc>:: exceptions() const {
        return exceptions_; 
    }

    template< class Ch, class Tr, class Alloc>
    unsigned char basic_format<Ch,Tr, Alloc>:: exceptions(unsigned char newexcept) { 
        unsigned char swp = exceptions_; 
        exceptions_ = newexcept; 
        return swp; 
    }

    template<class Ch, class Tr, class Alloc>
    void basic_format<Ch, Tr, Alloc>:: 
    make_or_reuse_data (std::size_t nbitems) {
#if !defined(BOOST_NO_STD_LOCALE)
        Ch fill = ( BOOST_USE_FACET(std::ctype<Ch>, getloc()) ). widen(' ');
#else
        Ch fill = ' ';
#endif
        if(items_.size() == 0)
            items_.assign( nbitems, format_item_t(fill) );
        else {
            if(nbitems>items_.size())
                items_.resize(nbitems, format_item_t(fill));
            bound_.resize(0);
            for(std::size_t i=0; i < nbitems; ++i)
                items_[i].reset(fill); //  strings are resized, instead of reallocated
        }
        prefix_.resize(0);
    }

    template< class Ch, class Tr, class Alloc>
    basic_format<Ch,Tr, Alloc>& basic_format<Ch,Tr, Alloc>:: 
    clear () {
        // empty the string buffers (except bound arguments)
        // and make the format object ready for formatting a new set of arguments

        BOOST_ASSERT( bound_.size()==0 || num_args_ == static_cast<int>(bound_.size()) );

        for(unsigned long i=0; i<items_.size(); ++i) {
            // clear converted strings only if the corresponding argument is not  bound :
            if( bound_.size()==0 || items_[i].argN_<0 || !bound_[ items_[i].argN_ ] )
                items_[i].res_.resize(0);
        }
        cur_arg_=0; dumped_=false;
        // maybe first arg is bound:
        if(bound_.size() != 0) {
            for(; cur_arg_ < num_args_ && bound_[cur_arg_]; ++cur_arg_)
                {}
        }
        return *this;
    }

    template< class Ch, class Tr, class Alloc>
    basic_format<Ch,Tr, Alloc>& basic_format<Ch,Tr, Alloc>:: 
    clear_binds () {
        // remove all binds, then clear()
        bound_.resize(0);
        clear();
        return *this;
    }

    template< class Ch, class Tr, class Alloc>
    basic_format<Ch,Tr, Alloc>& basic_format<Ch,Tr, Alloc>:: 
    clear_bind (int argN) {
        // remove the bind of ONE argument then clear()
        if(argN<1 || argN > num_args_ || bound_.size()==0 || !bound_[argN-1] ) {
            if( exceptions() & io::out_of_range_bit)
                boost::throw_exception(io::out_of_range(argN, 1, num_args_+1 ) ); 
            else return *this;
        }
        bound_[argN-1]=false;
        clear();
        return *this;
    }

    template< class Ch, class Tr, class Alloc>
    int basic_format<Ch,Tr, Alloc>::
    bound_args() const {
        if(bound_.size()==0)
            return 0;
        int n=0;
        for(int i=0; i<num_args_ ; ++i)
            if(bound_[i])
                ++n;
        return n;
    }

    template< class Ch, class Tr, class Alloc>
    int basic_format<Ch,Tr, Alloc>::
    fed_args() const {
        if(bound_.size()==0)
            return cur_arg_;
        int n=0;
        for(int i=0; i<cur_arg_ ; ++i)
            if(!bound_[i])
                ++n;
        return n;
    }

    template< class Ch, class Tr, class Alloc>
    int basic_format<Ch,Tr, Alloc>::
    cur_arg() const {
      return cur_arg_+1; }

    template< class Ch, class Tr, class Alloc>
    int basic_format<Ch,Tr, Alloc>::
    remaining_args() const {
        if(bound_.size()==0)
            return num_args_-cur_arg_;
        int n=0;
        for(int i=cur_arg_; i<num_args_ ; ++i)
            if(!bound_[i])
                ++n;
        return n;
    }

    template< class Ch, class Tr, class Alloc>
    typename basic_format<Ch, Tr, Alloc>::string_type 
    basic_format<Ch,Tr, Alloc>:: 
    str () const {
        if(items_.size()==0)
            return prefix_;
        if( cur_arg_ < num_args_)
            if( exceptions() & io::too_few_args_bit )
                // not enough variables supplied
                boost::throw_exception(io::too_few_args(cur_arg_, num_args_)); 

        unsigned long i;
        string_type res;
        res.reserve(size());
        res += prefix_;
        for(i=0; i < items_.size(); ++i) {
            const format_item_t& item = items_[i];
            res += item.res_;
            if( item.argN_ == format_item_t::argN_tabulation) { 
                BOOST_ASSERT( item.pad_scheme_ & format_item_t::tabulation);
                if( static_cast<size_type>(item.fmtstate_.width_) > res.size() )
                    res.append( static_cast<size_type>(item.fmtstate_.width_) - res.size(),
                                        item.fmtstate_.fill_ );
            }
            res += item.appendix_;
        }
        dumped_=true;
        return res;
    }
    template< class Ch, class Tr, class Alloc>
    typename std::basic_string<Ch, Tr, Alloc>::size_type  basic_format<Ch,Tr, Alloc>:: 
    size () const {
#ifdef BOOST_MSVC
       // If std::min<unsigned> or std::max<unsigned> are already instantiated
       // at this point then we get a blizzard of warning messages when we call
       // those templates with std::size_t as arguments.  Weird and very annoyning...
#pragma warning(push)
#pragma warning(disable:4267)
#endif
        BOOST_USING_STD_MAX();
        size_type sz = prefix_.size();
        unsigned long i;
        for(i=0; i < items_.size(); ++i) {
            const format_item_t& item = items_[i];
            sz += item.res_.size();
            if( item.argN_ == format_item_t::argN_tabulation)
                sz = max BOOST_PREVENT_MACRO_SUBSTITUTION (sz,
                                        static_cast<size_type>(item.fmtstate_.width_) );
            sz += item.appendix_.size();
        }
        return sz;
#ifdef BOOST_MSVC
#pragma warning(pop)
#endif
    }

namespace io {
namespace detail {

    template<class Ch, class Tr, class Alloc, class T> 
    basic_format<Ch, Tr, Alloc>&  
    bind_arg_body (basic_format<Ch, Tr, Alloc>& self, int argN, const T& val) {
        // bind one argument to a fixed value
        // this is persistent over clear() calls, thus also over str() and <<
        if(self.dumped_) 
            self.clear(); // needed because we will modify cur_arg_
        if(argN<1 || argN > self.num_args_) {
            if( self.exceptions() & io::out_of_range_bit )
                boost::throw_exception(io::out_of_range(argN, 1, self.num_args_+1 ) );
            else return self;
        }
        if(self.bound_.size()==0) 
            self.bound_.assign(self.num_args_,false);
        else 
            BOOST_ASSERT( self.num_args_ == static_cast<signed int>(self.bound_.size()) );
        int o_cur_arg = self.cur_arg_;
        self.cur_arg_ = argN-1; // arrays begin at 0

        self.bound_[self.cur_arg_]=false; // if already set, we unset and re-sets..
        self.operator%(val); // put val at the right place, because cur_arg is set
    

        // Now re-position cur_arg before leaving :
        self.cur_arg_ = o_cur_arg; 
        self.bound_[argN-1]=true;
        if(self.cur_arg_ == argN-1 ) {
            // hum, now this arg is bound, so move to next free arg
            while(self.cur_arg_ < self.num_args_ && self.bound_[self.cur_arg_])   
                ++self.cur_arg_;
        }
        // In any case, we either have all args, or are on an unbound arg :
        BOOST_ASSERT( self.cur_arg_ >= self.num_args_ || ! self.bound_[self.cur_arg_]);
        return self;
    }

    template<class Ch, class Tr, class Alloc, class T> basic_format<Ch, Tr, Alloc>&
    modify_item_body (basic_format<Ch, Tr, Alloc>& self, int itemN, T manipulator) {
        // applies a manipulator to the format_item describing a given directive.
        // this is a permanent change, clear or reset won't cancel that.
        if(itemN<1 || itemN > static_cast<signed int>(self.items_.size() )) {
            if( self.exceptions() & io::out_of_range_bit ) 
                boost::throw_exception(io::out_of_range(itemN, 1, static_cast<int>(self.items_.size()) ));
            else return self;
        }
        self.items_[itemN-1].fmtstate_. template apply_manip<T> ( manipulator );
        return self;
    }

} // namespace detail
} // namespace io
} // namespace boost



#endif  // BOOST_FORMAT_IMPLEMENTATION_HPP

/* format_implementation.hpp
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
*/