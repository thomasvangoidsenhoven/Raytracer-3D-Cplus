#pragma once

#include "samplers/sampler.h"

using namespace math;
using namespace std;
namespace raytracer
{
	namespace samplers
	{

		class RandomSampler : public raytracer::samplers::_private_::SamplerImplementation
		{
			private:
				int m_sample_count;

			public:
				RandomSampler(int m_sample_count = 0) : m_sample_count(m_sample_count) { }
				vector<Point2D> sample(const math::Rectangle2D& rectangle) const override;
		};

		/// <summary>
		/// Creates a sampler that always picks the n random points of the given rectangle
		/// </summary>
		Sampler random(int m_sample_count);
	}
}
