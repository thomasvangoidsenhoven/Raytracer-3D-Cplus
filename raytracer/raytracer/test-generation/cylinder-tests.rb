require './shared.rb'


test_file 'primitives/cylinder/cylinder-along-x/is-x-cylinder-hit' do
  template do
    <<-'END'
      #ifdef TEST_BUILD

      #include "Catch.h"
      #include "primitives/primitives.h"
      #include "math/approx.h"

      using namespace math;
      using namespace raytracer;
      using namespace raytracer::primitives;


      <<<TESTS>>>

      #endif
    END
  end

  test_suite do
    template do
      <<-END
        TEST_CASE("[CylinderX] Is cylinder hit with ray #{ray_origin} + #{ray_direction} * t", "[CylinderX]")
        {
            Point3D ray_origin#{ray_origin};
            Vector3D ray_direction#{ray_direction};

            auto cylinder = raytracer::primitives::cylinder_along_x();
            Ray ray(ray_origin, ray_direction);

            Hit hit;
            bool is_hit = cylinder->find_first_positive_hit(ray, &hit);
            REQUIRE(is_hit == #{expected_is_hit});
        }
      END
    end

    [-7, 0, 3].each do |x|
      [-5, -1.01, -0.99, 0, 0.99, 1.01, 9].each do |y|
        test_case do |data|
          data.ray_origin = "(#{x}, #{y}, 5)"
          data.ray_direction = "(0, 0, -1)"
          data.expected_is_hit = if -1 < y and y < 1 then 'true' else 'false' end                                   
        end
      end
    end    
  end
end

test_file 'primitives/cylinder/cylinder-along-x/x-cylinder-t' do
  template do
    <<-'END'
      #ifdef TEST_BUILD

      #include "Catch.h"
      #include "primitives/primitives.h"
      #include "math/approx.h"

      using namespace math;
      using namespace raytracer;
      using namespace raytracer::primitives;


      <<<TESTS>>>

      #endif
    END
  end

  test_suite do
    template do
      <<-END
        TEST_CASE("[CylinderX] t-values of hits with ray #{ray_origin} + #{ray_direction} * t", "[CylinderX]")
        {
            Point3D ray_origin#{ray_origin};
            Vector3D ray_direction#{ray_direction};

            auto cylinder = raytracer::primitives::cylinder_along_x();
            Ray ray(ray_origin, ray_direction);

            auto hits = cylinder->find_all_hits(ray);

            REQUIRE(hits.size() == 2);
            CHECK(hits[0]->t == Approx(#{expected_t1}));
            CHECK(hits[1]->t == Approx(#{expected_t2}));
        }
      END
    end

    [-7, 0, 3].each do |x|
      [-7, -3, 0, 2].each do |z|
        test_case do |data|
          data.ray_origin = "(#{x}, 0, #{z})"
          data.ray_direction = "(0, 0, 1)"
          data.expected_t1 = -1 - z
          data.expected_t2 = 1 - z
        end
      end
    end    

    [-7, 0, 3].each do |x|
      [-7, -3, 0, 2].each do |y|
        test_case do |data|
          data.ray_origin = "(#{x}, #{y}, 0)"
          data.ray_direction = "(0, 1, 0)"
          data.expected_t1 = -1 - y
          data.expected_t2 = 1 - y
        end
      end
    end    
  end
end

test_file 'primitives/cylinder/cylinder-along-x/x-cylinder-n' do
  template do
    <<-'END'
      #ifdef TEST_BUILD

      #include "Catch.h"
      #include "primitives/primitives.h"
      #include "math/approx.h"

      using namespace math;
      using namespace raytracer;
      using namespace raytracer::primitives;


      <<<TESTS>>>

      #endif
    END
  end

  test_suite do
    template do
      <<-END
        TEST_CASE("[CylinderX] Normals of hits with ray #{ray_origin} + #{ray_direction} * t", "[CylinderX]")
        {
            Point3D ray_origin#{ray_origin};
            Vector3D ray_direction#{ray_direction};

            auto cylinder = raytracer::primitives::cylinder_along_x();
            Ray ray(ray_origin, ray_direction);

            auto hits = cylinder->find_all_hits(ray);

            REQUIRE(hits.size() == 2);
            CHECK(hits[0]->normal == approx(Vector3D#{expected_n1}));
            CHECK(hits[1]->normal == approx(Vector3D#{expected_n2}));
        }
      END
    end

    [-11, -7, 0, 3, 8].each do |x|
      [-7, -3, -1.01].each do |z|
        test_case do |data|
          data.ray_origin = "(#{x}, 0, #{z})"
          data.ray_direction = "(0, 0, 1)"
          data.expected_n1 = "(0, 0, -1)"
          data.expected_n2 = "(0, 0, -1)"
        end
      end
    end    

    [-11, -7, 0, 3, 8].each do |x|
      [-0.99, -0.4, 0, 0.5, 0.99].each do |z|
        test_case do |data|
          data.ray_origin = "(#{x}, 0, #{z})"
          data.ray_direction = "(0, 0, 1)"
          data.expected_n1 = "(0, 0, 1)"
          data.expected_n2 = "(0, 0, -1)"
        end
      end
    end    
  end
end
