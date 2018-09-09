require './shared.rb'

file_template = proc do
  <<-'END'
    #ifdef TEST_BUILD

    #include "Catch.h"
    #include "primitives/primitives.h"
    #include "math/approx.h"
    #include <algorithm>

    using namespace math;
    using namespace raytracer;
    using namespace raytracer::primitives;


    <<<TESTS>>>

    #endif
  END
end  


test_file 'primitives/triangle/is-triangle-hit' do
  template(&file_template)

  test_suite do
    template do
      <<-END
        TEST_CASE("[Triangle] Is there hit between Triangle #{a} #{b} #{c} and Ray #{ray_origin} + #{ray_direction} * t", "[Triangle]")
        {
            Point3D ray_origin#{ray_origin};
            Vector3D ray_direction#{ray_direction};
            Point3D a#{a};
            Point3D b#{b};
            Point3D c#{c};

            auto primitive = raytracer::primitives::triangle(a, b, c);
            Ray ray(ray_origin, ray_direction);

            Hit hit;
            bool is_hit = primitive->find_first_positive_hit(ray, &hit);

            REQUIRE(is_hit == #{expected_is_hit});
        }
      END
    end

    [-7, -1, -0.001, 0.001, 0.5, 0.99, 1.01, 1.5].each do |x|
      test_case do |data|
        data.a = "(0, 0, 0)"
        data.b = "(2, 0, 0)"
        data.c = "(0, 2, 0)"
        data.ray_origin = "(#{x}, 1, 1)"
        data.ray_direction = "(0, 0, -1)"
        data.expected_is_hit = if 0 < x && x < 1 then 'true' else 'false' end
      end

      test_case do |data|
        data.a = "(0, 0, 0)"
        data.b = "(2, 0, 0)"
        data.c = "(0, 2, 0)"
        data.ray_origin = "(#{x}, 1, -1)"
        data.ray_direction = "(0, 0, 1)"
        data.expected_is_hit = if 0 < x && x < 1 then 'true' else 'false' end
      end
    end

    [-7, -1, -0.001, 0.001, 0.5, 1.99, 2.01, 2.5].each do |x|
      test_case do |data|
        data.a = "(0, 0, 0)"
        data.b = "(4, 0, 0)"
        data.c = "(0, 4, 0)"
        data.ray_origin = "(#{x}, 2, 5)"
        data.ray_direction = "(0, 0, -0.5)"
        data.expected_is_hit = if 0 < x && x < 2 then 'true' else 'false' end
      end

      test_case do |data|
        data.a = "(0, 0, 0)"
        data.b = "(4, 0, 0)"
        data.c = "(0, 4, 0)"
        data.ray_origin = "(#{x}, 2, -7)"
        data.ray_direction = "(0, 0, 0.25)"
        data.expected_is_hit = if 0 < x && x < 2 then 'true' else 'false' end
      end
    end

    [-8, 0.5, 1.5, 2.5, 2.99, 3.01, 5, 5.99, 6.01, 7, 99].each do |x|
      test_case do |data|
        data.a = "(0, 0, 0)"
        data.b = "(6, 6, 0)"
        data.c = "(6, 0, 0)"
        data.ray_origin = "(#{x}, 3, 5)"
        data.ray_direction = "(0, 0, -0.5)"
        data.expected_is_hit = if 3 < x && x < 6 then 'true' else 'false' end
      end
    end

    [-5, 0, 5, 9.99, 10.01, 10.99, 11.01, 19].each do |y|
      test_case do |data|
        data.a = "(0, 10, 10)"
        data.b = "(0, 10, 18)"
        data.c = "(0, 12, 18)"
        data.ray_origin = "(5, #{y}, 14)"
        data.ray_direction = "(-5, 0, 0)"
        data.expected_is_hit = if 10 < y && y < 11 then 'true' else 'false' end
      end
    end

    [-5, 0, 5, 9.99, 10.01, 10.99, 11.01, 19].each do |y|
      test_case do |data|
        data.a = "(-7, 10, 10)"
        data.b = "(-3, 10, 18)"
        data.c = "(-11, 12, 18)"
        data.ray_origin = "(5, #{y}, 14)"
        data.ray_direction = "(-5, 0, 0)"
        data.expected_is_hit = if 10 < y && y < 11 then 'true' else 'false' end
      end
    end
  end

  test_suite do
    template do
      <<-END
        TEST_CASE("[Triangle] Is there hit between Triangle #{a} #{b} #{c} and Ray starting at #{ray_origin} through u=#{u} v=#{v}", "[Triangle]")
        {
            Point3D ray_origin#{ray_origin};
            Point3D a#{a};
            Point3D b#{b};
            Point3D c#{c};
            Vector3D ab = b - a;
            Vector3D ac = c - a;
            double u = #{u};
            double v = #{v};
            Point3D p = a + ab * u + ac * v;
            Vector3D ray_direction = p - ray_origin;

            auto primitive = raytracer::primitives::triangle(a, b, c);
            Ray ray(ray_origin, ray_direction);

            Hit hit;
            bool is_hit = primitive->find_first_positive_hit(ray, &hit);

            REQUIRE(is_hit == #{expected_is_hit});
        }
      END
    end

    [1, 1.5, 6].each do |x|
      [0.3, 1.2, 7].each do |y|
        [-0.1, 0.2, 0.49, 0.7, 1.5].each do |u|
          [-0.6, 0.25, 0.49, 0.6, 1.7, 9].each do |v|
            test_case do |data|
              data.a = "(0, 0, 0)"
              data.b = "(#{x}, 0, 0)"
              data.c = "(0, #{y}, 0)"
              data.ray_origin = "(0, 0, 5)"
              data.u = u
              data.v = v
              data.expected_is_hit = if 0 < u && 0 < v && u + v < 1  then 'true' else 'false' end
            end
          end
        end           
      end
    end
  end
end

test_file 'primitives/triangle/triangle-t' do
  template(&file_template)

  test_suite do
    template do
      <<-END
        TEST_CASE("[Triangle] Expecting t=#{t} for for hit between Triangle #{a} #{b} #{c} and Ray O=#{ray_origin} through u=#{u} v=#{v}", "[Triangle]")
        {
            Point3D ray_origin#{ray_origin};
            Point3D a#{a};
            Point3D b#{b};
            Point3D c#{c};
            Vector3D ab = b - a;
            Vector3D ac = c - a;
            double u = #{u};
            double v = #{v};
            Point3D p = a + ab * u + ac * v;
            double t = #{t};
            Vector3D ray_direction = (p - ray_origin) / t;

            auto primitive = raytracer::primitives::triangle(a, b, c);
            Ray ray(ray_origin, ray_direction);

            Hit hit;
            bool is_hit = primitive->find_first_positive_hit(ray, &hit);

            REQUIRE(is_hit);
            REQUIRE(hit.t == Approx(t));
        }
      END
    end

    [0.01, 0.1, 0.2, 0.3, 0.4, 0.49].each do |u|
      [0.01, 0.1, 0.2, 0.3, 0.4, 0.49].each do |v|
        [0.5, 1, 9].each do |x|
          [0.2, 1, 6].each do |y|
            [0.1, 1, 5].each do |t|
              test_case do |data|
                data.a = "(0, 0, 1)"
                data.b = "(#{x}, 0, 2)"
                data.c = "(0, #{y}, 3)"
                data.ray_origin = "(#{x}, 1, 1)"
                data.u = u
                data.v = v
                data.t = t
              end
            end
          end
        end
      end
    end
  end
end

test_file 'primitives/triangle/triangle-normal' do
  template(&file_template)

  test_suite do
    template do
      <<-END
        TEST_CASE("[Triangle] Expecting normal #{expected_n} for for hit between Triangle #{a} #{b} #{c} and Ray O=#{ray_origin} through u=#{u} v=#{v}", "[Triangle]")
        {
            Point3D ray_origin#{ray_origin};
            Point3D a#{a};
            Point3D b#{b};
            Point3D c#{c};
            Vector3D ab = b - a;
            Vector3D ac = c - a;
            double u = #{u};
            double v = #{v};
            Point3D p = a + ab * u + ac * v;
            Vector3D ray_direction = p - ray_origin;

            auto primitive = raytracer::primitives::triangle(a, b, c);
            Ray ray(ray_origin, ray_direction);

            Hit hit;
            bool is_hit = primitive->find_first_positive_hit(ray, &hit);

            REQUIRE(is_hit);
            REQUIRE(hit.normal == approx(Vector3D#{expected_n}));
        }
      END
    end

    [0.01, 0.3, 0.4, 0.6, 0.99].each do |u|
      [0.01, 0.3, 0.4, 0.6, 0.99].each do |v|
        [0.5, 1, 15].each do |x|
          [0.2, 1, 3].each do |y|
            if u + v < 1
              test_case do |data|
                data.a = "(0, 0, 0)"
                data.b = "(#{x}, 0, 0)"
                data.c = "(0, #{y}, 0)"
                data.ray_origin = "(5, 1, 1)"
                data.u = u
                data.v = v
                data.expected_n = '(0, 0, 1)'
              end

              test_case do |data|
                data.a = "(0, 0, 0)"
                data.b = "(#{x}, 0, 0)"
                data.c = "(0, #{y}, 0)"
                data.ray_origin = "(5, 7, -2)"
                data.u = u
                data.v = v
                data.expected_n = '(0, 0, -1)'
              end
            end
          end
        end
      end
    end

    [0.01, 0.3, 0.4, 0.6, 0.99].each do |u|
      [0.01, 0.3, 0.4, 0.6, 0.99].each do |v|
        [0.5, 1, 15].each do |x|
          [0.2, 1, 3].each do |z|
            if u + v < 1
              test_case do |data|
                data.a = "(0, 0, 0)"
                data.b = "(#{x}, 0, 0)"
                data.c = "(0, 0, #{z})"
                data.ray_origin = "(7, 3, 8)"
                data.u = u
                data.v = v
                data.expected_n = '(0, 1, 0)'
              end

              test_case do |data|
                data.a = "(0, 0, 0)"
                data.b = "(#{x}, 0, 0)"
                data.c = "(0, 0, #{z})"
                data.ray_origin = "(2, -3, 6)"
                data.u = u
                data.v = v
                data.expected_n = '(0, -1, 0)'
              end
            end
          end
        end
      end
    end

    [0.01, 0.3, 0.4, 0.6, 0.99].each do |u|
      [0.01, 0.3, 0.4, 0.6, 0.99].each do |v|
        [0.5, 1, 15].each do |y|
          [0.2, 1, 3].each do |z|
            if u + v < 1
              test_case do |data|
                data.a = "(0, 0, 0)"
                data.b = "(0, #{y}, 0)"
                data.c = "(0, 0, #{z})"
                data.ray_origin = "(1, 7, 6)"
                data.u = u
                data.v = v
                data.expected_n = '(1, 0, 0)'
              end

              test_case do |data|
                data.a = "(0, 0, 0)"
                data.b = "(0, #{y}, 0)"
                data.c = "(0, 0, #{z})"
                data.ray_origin = "(-5, 5, 5)"
                data.u = u
                data.v = v
                data.expected_n = '(-1, 0, 0)'
              end
            end
          end
        end
      end
    end        
  end
end

test_file 'primitives/triangle/triangle-position' do
  template(&file_template)

  test_suite do
    template do
      <<-END
        TEST_CASE("[Triangle] Checking position for for hit between Triangle #{a} #{b} #{c} and Ray O=#{ray_origin} through u=#{u} v=#{v}", "[Triangle]")
        {
            Point3D ray_origin#{ray_origin};
            Point3D a#{a};
            Point3D b#{b};
            Point3D c#{c};
            Vector3D ab = b - a;
            Vector3D ac = c - a;
            double u = #{u};
            double v = #{v};
            Point3D p = a + ab * u + ac * v;
            Vector3D ray_direction = p - ray_origin;

            auto primitive = raytracer::primitives::triangle(a, b, c);
            Ray ray(ray_origin, ray_direction);

            Hit hit;
            bool is_hit = primitive->find_first_positive_hit(ray, &hit);

            REQUIRE(is_hit);
            REQUIRE(hit.position == approx(p));
        }
      END
    end

    [0.01, 0.3, 0.4, 0.6, 0.99].each do |u|
      [0.01, 0.3, 0.4, 0.6, 0.99].each do |v|
        [-75, -18, 14, 99].each do |ox|
          [-7, 3].each do |ax|
            [-5, 13].each do |by|
              [-4, 64].each do |cz|
                if u + v < 1
                  test_case do |data|
                    data.a = "(#{ax}, 0, 0)"
                    data.b = "(1, #{by}, 0)"
                    data.c = "(0, 1, #{cz})"
                    data.ray_origin = "(#{ox}, 67, 13)"
                    data.u = u
                    data.v = v
                  end

                  test_case do |data|
                    data.a = "(#{ax}, 7, 3)"
                    data.b = "(10, #{by}, 1)"
                    data.c = "(8, 4, #{cz})"
                    data.ray_origin = "(#{ox}, 7, 13)"
                    data.u = u
                    data.v = v
                  end
                end
              end
            end
          end
        end
      end
    end
  end
end
