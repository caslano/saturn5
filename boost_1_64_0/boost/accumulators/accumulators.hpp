///////////////////////////////////////////////////////////////////////////////
/// \file accumulators.hpp
/// Includes all of the Accumulators Framework
//
//  Copyright 2005 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_ACCUMULATORS_HPP_EAN_28_10_2005
#define BOOST_ACCUMULATORS_ACCUMULATORS_HPP_EAN_28_10_2005

#include <boost/accumulators/framework/accumulator_set.hpp>
#include <boost/accumulators/framework/accumulator_concept.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/framework/external.hpp>
#include <boost/accumulators/framework/features.hpp>
#include <boost/accumulators/framework/parameters/accumulator.hpp>
#include <boost/accumulators/framework/parameters/sample.hpp>
#include <boost/accumulators/framework/parameters/weight.hpp>
#include <boost/accumulators/framework/parameters/weights.hpp>
#include <boost/accumulators/framework/accumulators/external_accumulator.hpp>
#include <boost/accumulators/framework/accumulators/droppable_accumulator.hpp>
#include <boost/accumulators/framework/accumulators/reference_accumulator.hpp>
#include <boost/accumulators/framework/accumulators/value_accumulator.hpp>

#endif

/* accumulators.hpp
+tbx/P479ZtAApPOENip4c84uxq63MFvAqzlZ5wyd6Mu4fsOlQnfHmH85w2K5wsRslcYABKCkYrjnhII/P4bIFDg1v0CB7lXao1MO0OAE0/pOTTdrBQoo79gGmzaCo66xQ6Uwc/4wl+KY6Q1XJdl28tz9lXA34mPA3/jVoBs5hhkg7enRPpE6XOZPgf7PKW/pO+VZhqGQPrMNOeQfVKx4m5S3F8ogW0O6lw1AJM19NVS9BVbrrW+YH/8XPtYh6X5KoflC7gtcBvhVsOF4V6DywCYP4PrC3ckXDJcHFxzvsPyZf7/39zXifczicVKVUa9zuwRWPghq/3aOphIK86cenQScz5KHOa9y2wK/ktUwh/TxIf/KcIqP+GP8SoJ4k88QoTPzj53BOvXkD3O0J94QnjLq71VsmtasZcyB761TnNRiRhVYvcK3sdnq4BhzksVMNz2OV+qm1lx+qTv7Qp8iEM6r61ukY3gbvoYtvX9cbu+DRzBCdeXgb2e7u0vIps+bhPVvw5L9/TSnJJ1hUm+4LFK8Nf2rEC5I1IZiNidcy6PCPpzoUx6YTKFTNRSVY34sKsOPi9t2Gst0OV2a+MSB69ANXrRuqZIoNla1I8+bvywKVJSVrSF/JbvmyKLrKahlrtM/N13f49eVEZ1jDDqiL/gPLmlE9ZJ2m4cHWMzJtjF6Xe8gmTaxanudYMvdTjnlQfuSrYUHekl6TLbtq3Vt4P7bDg+CGMHNZTpQohKXK2fDOG8WqU+9EMDPk1YStEO5VFMWMYzxBBhEkAHYuPmLgOjm/hrl0W+ZwrbvovO7RVX5DJtibZx1cBKxT7zV0bzq+PwzFSvWnVIz8LukbJAs2vKNuQURezb3i3+M8E6nN/Xcyys67qxxdsxS5si+nkLm2DHRN/Ivs/8K7bK/B9cGM2/YQnyf7/AzP+D9BIQJSBp6Pji39PuFU8WbfRrazFW43znzkqZATOuokwlEoYhF4aX47atvD7BpBm9UjOjLMWSNSSp8BjR5voskNVMVG3Q0iLMwhHhDVSxp5NC5vbnFwxxf0ghC0wsjudXXe2yYMWFEd+yy1yWpDBAVm38rCgsWWmZDeMjN4FC4rBzSQqHtzjow45MYKLIG5+0loTlSaugvqDzJ1Xi/AnJ23EApxoi9C1HkgTdgklfWwWFAB3cXOsOIxi7kxbhSI5C1tYbgnyS4yOM5fiKu1oI8hGAyt3h9lOicoulUQHP0pA88+NGfCSRJW51uMGuzNyM7KTfQFDSxlOAVqc/dFY8UMD9EbgQNplaVeHR4S3HElsTlxTW1pO/Bv6GI8NbjsOzIfUcCC/OA2nvcRlJG71a7cyPyUv1WyxlFpBAFhQSUAbl0K0Ua5WZZICXiMYCID+QSskSLFlrdaz1dpHLRRHkpfGIg5291KS1HLPJaoFaJcGfVK3VDNUeLSGFC4IRDrVJD2/Sow9a+HHJChQ3NOnRkNCr1A5NuuJBC2pERSjJq61HIb0JkBMwy9QQbDM3z0BGqrUGO6kH+dBouN5Jihjna+uVcAOdL00cmjSnhHQ93qQ5IVLI4PtBi521VdyMSAQY9SVtTFqLU6jHhledEDzaG7zKruI0QtaQvc45T0suwtUFU/gh/WHkgBU7Os+Fmc7uKrXSGsk+hbxxwhsHr014bbTcCq+d1mDhjadVWXgT4E0U3sRO4AJWwIOHHGupiB3f2ErJFWXPZmNF+eKsFisKHUZuVINxKpaWINaBejVQEyFBhxqpGGRPKmrG82Lj1mNNwWvU91qsUXtVH0A7TSs/pZ/FMmNqIsx/qzbxFDU1C4FOM7CRAh1a+dS+pySagc1YAx7xxZV5M+yD6onJaBmHmPqZCFU=
*/