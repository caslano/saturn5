// Copyright Daniel Wallin 2007. Use, modification and distribution is
// subject to the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_SHUFFLED_DISTRIBUTION_070923_HPP
#define BOOST_SHUFFLED_DISTRIBUTION_070923_HPP

#ifndef BOOST_GRAPH_USE_MPI
#error "Parallel BGL files should not be included unless <boost/graph/use_mpi.hpp> has been included"
#endif

# include <boost/assert.hpp>
# include <boost/iterator/counting_iterator.hpp>
# include <vector>

namespace boost { namespace graph { namespace distributed {

template <class BaseDistribution>
struct shuffled_distribution : BaseDistribution
{
    typedef std::size_t size_type;

    template <class ProcessGroup>
    shuffled_distribution(ProcessGroup const& pg, BaseDistribution const& base)
      : BaseDistribution(base)
      , n(num_processes(pg))
      , mapping_(make_counting_iterator(size_type(0)), make_counting_iterator(n))
      , reverse_mapping(mapping_)
    {}

    std::vector<size_type> const& mapping() const
    {
        return mapping_;
    }

    template <class InputIterator>
    void assign_mapping(InputIterator first, InputIterator last)
    {
        mapping_.assign(first, last);
        BOOST_ASSERT(mapping_.size() == n);
        reverse_mapping.resize(mapping_.size());

        for (std::vector<size_t>::iterator i(mapping_.begin());
            i != mapping_.end(); ++i)
        {
            reverse_mapping[*i] = i - mapping_.begin();
        }
    }

    BaseDistribution& base()
    {
        return *this;
    }

    BaseDistribution const& base() const
    {
        return *this;
    }

    template <class ProcessID>
    size_type block_size(ProcessID id, size_type n) const
    {
        return base().block_size(reverse_mapping[id], n);
    }

    template <class T>
    size_type operator()(T const& value) const
    {
        return mapping_[base()(value)];
    }

    template <class ProcessID>
    size_type start(ProcessID id) const
    {
        return base().start(reverse_mapping[id]);
    }

    size_type local(size_type i) const
    {
        return base().local(i);
    }

    size_type global(size_type i) const
    {
        return base().global(i);
    }

    template <class ProcessID>
    size_type global(ProcessID id, size_type n) const
    {
        return base().global(reverse_mapping[id], n);
    }

    template <class Archive>
    void serialize(Archive& ar, unsigned long /*version*/)
    {
        ar & serialization::make_nvp("base", base());
    }

    void clear() 
    {
        base().clear();
    }

private:
    size_type n;
    std::vector<size_type> mapping_;
    std::vector<size_type> reverse_mapping;
};

}}} // namespace boost::graph::distributed

#endif // BOOST_SHUFFLED_DISTRIBUTION_070923_HPP


/* shuffled_distribution.hpp
L2Likhdw5hKcRJsV1rEP+HMInCD9zeDsUpvdUVAOtOxQHFiji1OqCopSSpfYCmzYB+ESYXEcb13iWJppt5VWLoXYv/v4xxUV2aAMDHMY8KBOhNVUTKVHCbNKoAGKZheBFR4QS4sO0WUYm1JQY0/AORz6DsMJlctKbVWV2B/ZBbbSgiVY2MbAkhEJ3ntlDPR8U2AMhHeLsEA0zNwqBtrZVlsNtDohgOEsa0V1RoG9BIIDQTQc0IJMcKaV7AzE2aHySxx2aw3ERlE5EPrVK0ZBRn9qQXW10EKnxeDPLrUuTy8mPflk8PzKiitiXhfasHQZyAe0RzHEUYkA05/0e2FFNVC6M2FeWkKKT5rvZSwWLnZBXEZc7uzYuximBsI8hHMhAsPK4PzlhTWlhVWQ+dkQ8NoKS2zMU+irLKxekV/D3B5SYa0QvExWCLIR/O+I8yuWAGYFSBNHqaB/RHD+sprKauh5ezHDPCzJr6kuL7VXQ5Mh1uyQGiEJAqeC8pda7YXLi5h/R372KqCHeaJDwGOvgigMpROeBXb0v054YglXhyzzE2IySB6IZp4DftDwpCQ1ovz8WdXVuYXV2COgb8y4oPyCipql+dbaUpDdjuBiIun1QLUA9SS/0GaHXs0vBYWG7BWM1+/PtzKpmdmz5ikUrNCy1dCSioDtnflxCbG50KJ3BiGZ/CJUgKVWW35JVdU9DPMalAWi51eWEF0q
*/