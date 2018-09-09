require './shared.rb'


test_file 'primitives/plane/xy-plane/xy-plane-t' do
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
        TEST_CASE("[XY Plane] t-value of hits with Ray #{ray_origin} + #{ray_direction} * t", "[XY Plane]")
        {
            Point3D ray_origin#{ray_origin};
            Vector3D ray_direction#{ray_direction};

            auto primitive = raytracer::primitives::xy_plane();
            Ray ray(ray_origin, ray_direction);

            auto hits = primitive->find_all_hits(ray);

            REQUIRE(hits.size() == 1);
            CHECK(hits[0]->t == Approx(#{expected_t}));
        }
      END
    end

    [-2, 0, 3.1].each do |x|
      [-2.7, 0, 8.6].each do |y|
        [-7, 1, 5, 10].each do |z|
          [-5.78, 1.0, 2.0, 6.1].each do |dz|
            test_case do |data|
              data.ray_origin = "(#{x}, #{y}, #{z})"
              data.ray_direction = "(0, 0, #{dz})"
              data.expected_t = -z / dz
            end
          end         
        end
      end
    end
  end
end

test_file 'primitives/plane/xy-plane/xy-plane-n' do
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
        TEST_CASE("[XY Plane] Normal of hits with Ray #{ray_origin} + #{ray_direction} * t", "[XY Plane]")
        {
            Point3D ray_origin#{ray_origin};
            Vector3D ray_direction#{ray_direction};

            auto primitive = raytracer::primitives::xy_plane();
            Ray ray(ray_origin, ray_direction);

            auto hits = primitive->find_all_hits(ray);

            REQUIRE(hits.size() == 1);
            CHECK(hits[0]->normal == approx(Vector3D#{expected_normal}));
        }
      END
    end

    [-2, 0, 2].each do |x|
      [-2, 0, 2].each do |y|
        [1, 5, 10].each do |z|
          [-4.5, 1.0, 2.0].each do |dz|
            test_case do |data|
              data.ray_origin = "(#{x}, #{y}, #{z})"
              data.ray_direction = "(0, 0, #{dz})"
              data.expected_normal = "(0, 0, 1)"
            end

            test_case do |data|
              data.ray_origin = "(#{x}, #{y}, -#{z})"
              data.ray_direction = "(0, 0, #{dz})"
              data.expected_normal = "(0, 0, -1)"
            end
          end         
        end
      end
    end
  end
end

test_file 'primitives/plane/xy-plane/xy-plane-position' do
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
        TEST_CASE("[XY Plane] Position of hits with Ray #{ray_origin} + #{ray_direction} * t", "[XY Plane]")
        {
            Point3D ray_origin#{ray_origin};
            Vector3D ray_direction#{ray_direction};

            auto primitive = raytracer::primitives::xy_plane();
            Ray ray(ray_origin, ray_direction);

            auto hits = primitive->find_all_hits(ray);

            REQUIRE(hits.size() == 1);
            CHECK(hits[0]->position == approx(Point3D#{expected_position}));
        }
      END
    end

    [-5.7, 0, 9.1].each do |x|
      [-7.7, 0, 2.6].each do |y|
        [-7.1, 1.6, 5.4, 10.1].each do |z|
          [-4.5, 1.0, 2.0].each do |dz|
            test_case do |data|
              data.ray_origin = "(#{x}, #{y}, #{z})"
              data.ray_direction = "(0, 0, #{dz})"
              data.expected_position = "(#{x}, #{y}, 0)"
            end
          end         
        end
      end
    end
  end
end

test_file 'primitives/plane/xy-plane/xy-plane-xyz' do
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
        TEST_CASE("[XY Plane] Local position xyz of hits with Ray #{ray_origin} + #{ray_direction} * t", "[XY Plane]")
        {
            Point3D ray_origin#{ray_origin};
            Vector3D ray_direction#{ray_direction};

            auto primitive = raytracer::primitives::xy_plane();
            Ray ray(ray_origin, ray_direction);

            auto hits = primitive->find_all_hits(ray);

            REQUIRE(hits.size() == 1);
            CHECK(hits[0]->local_position.xyz == approx(Point3D#{expected_xyz}));
        }
      END
    end

    [-5.7, 0, 9.1].each do |x|
      [-7.7, 0, 2.6].each do |y|
        [-7.1, 1.6, 5.4, 10.1].each do |z|
          [-4.5, 1.0, 2.0].each do |dz|
            test_case do |data|
              data.ray_origin = "(#{x}, #{y}, #{z})"
              data.ray_direction = "(0, 0, #{dz})"
              data.expected_xyz = "(#{x}, #{y}, 0)"
            end
          end         
        end
      end
    end
  end
end

test_file 'primitives/plane/xy-plane/xy-plane-uv' do
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
        TEST_CASE("[XY Plane] Local position uv of hits with Ray #{ray_origin} + #{ray_direction} * t", "[XY Plane]")
        {
            Point3D ray_origin#{ray_origin};
            Vector3D ray_direction#{ray_direction};

            auto primitive = raytracer::primitives::xy_plane();
            Ray ray(ray_origin, ray_direction);

            auto hits = primitive->find_all_hits(ray);

            REQUIRE(hits.size() == 1);
            CHECK(hits[0]->local_position.uv == approx(Point2D#{expected_uv}));
        }
      END
    end

    [-5.7, 0, 9.1].each do |x|
      [-7.7, 0, 2.6].each do |y|
        [-7.1, 1.6, 5.4, 10.1].each do |z|
          [-4.5, 1.0, 2.0].each do |dz|
            test_case do |data|
              data.ray_origin = "(#{x}, #{y}, #{z})"
              data.ray_direction = "(0, 0, #{dz})"
              data.expected_uv = "(#{x}, #{y})"
            end
          end         
        end
      end
    end
  end
end


test_file 'primitives/plane/xz-plane/xz-plane-t' do
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
        TEST_CASE("[XZ Plane] t-value of hits with Ray #{ray_origin} + #{ray_direction} * t", "[XZ Plane]")
        {
            Point3D ray_origin#{ray_origin};
            Vector3D ray_direction#{ray_direction};

            auto primitive = raytracer::primitives::xz_plane();
            Ray ray(ray_origin, ray_direction);

            auto hits = primitive->find_all_hits(ray);

            REQUIRE(hits.size() == 1);
            CHECK(hits[0]->t == Approx(#{expected_t}));
        }
      END
    end

    [-2, 0, 3.1].each do |x|
      [-2.7, 0, 8.6].each do |z|
        [-7, 1, 5, 10].each do |y|
          [-5.78, 1.0, 2.0, 6.1].each do |dy|
            test_case do |data|
              data.ray_origin = "(#{x}, #{y}, #{z})"
              data.ray_direction = "(0, #{dy}, 0)"
              data.expected_t = -y / dy
            end
          end         
        end
      end
    end
  end
end

test_file 'primitives/plane/xz-plane/xz-plane-n' do
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
        TEST_CASE("[XZ Plane] Normal of hits with Ray #{ray_origin} + #{ray_direction} * t", "[XZ Plane]")
        {
            Point3D ray_origin#{ray_origin};
            Vector3D ray_direction#{ray_direction};

            auto primitive = raytracer::primitives::xz_plane();
            Ray ray(ray_origin, ray_direction);

            auto hits = primitive->find_all_hits(ray);

            REQUIRE(hits.size() == 1);
            CHECK(hits[0]->normal == approx(Vector3D#{expected_normal}));
        }
      END
    end

    [-2, 0, 2].each do |x|
      [-2, 0, 2].each do |z|
        [1, 5, 10].each do |y|
          [-4.5, 1.0, 2.0].each do |dy|
            test_case do |data|
              data.ray_origin = "(#{x}, #{y}, #{z})"
              data.ray_direction = "(0, #{dy}, 0)"
              data.expected_normal = "(0, 1, 0)"
            end

            test_case do |data|
              data.ray_origin = "(#{x}, -#{y}, #{z})"
              data.ray_direction = "(0, #{dy}, 0)"
              data.expected_normal = "(0, -1, 0)"
            end
          end         
        end
      end
    end
  end
end


test_file 'primitives/plane/xz-plane/xz-plane-position' do
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
        TEST_CASE("[XZ Plane] Position of hits with Ray #{ray_origin} + #{ray_direction} * t", "[XZ Plane]")
        {
            Point3D ray_origin#{ray_origin};
            Vector3D ray_direction#{ray_direction};

            auto primitive = raytracer::primitives::xz_plane();
            Ray ray(ray_origin, ray_direction);

            auto hits = primitive->find_all_hits(ray);

            REQUIRE(hits.size() == 1);
            CHECK(hits[0]->position == approx(Point3D#{expected_position}));
        }
      END
    end

    [-5.7, 0, 9.1].each do |x|
      [-7.7, 0, 2.6].each do |z|
        [-7.1, 1.6, 5.4, 10.1].each do |y|
          [-4.5, 1.0, 2.0].each do |dy|
            test_case do |data|
              data.ray_origin = "(#{x}, #{y}, #{z})"
              data.ray_direction = "(0, #{dy}, 0)"
              data.expected_position = "(#{x}, 0, #{z})"
            end
          end         
        end
      end
    end
  end
end

test_file 'primitives/plane/xz-plane/xz-plane-xyz' do
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
        TEST_CASE("[XZ Plane] Local position xyz of hits with Ray #{ray_origin} + #{ray_direction} * t", "[XZ Plane]")
        {
            Point3D ray_origin#{ray_origin};
            Vector3D ray_direction#{ray_direction};

            auto primitive = raytracer::primitives::xz_plane();
            Ray ray(ray_origin, ray_direction);

            auto hits = primitive->find_all_hits(ray);

            REQUIRE(hits.size() == 1);
            CHECK(hits[0]->local_position.xyz == approx(Point3D#{expected_xyz}));
        }
      END
    end

    [-5.7, 0, 9.1].each do |x|
      [-7.7, 0, 2.6].each do |z|
        [-7.1, 1.6, 5.4, 10.1].each do |y|
          [-4.5, 1.0, 2.0].each do |dy|
            test_case do |data|
              data.ray_origin = "(#{x}, #{y}, #{z})"
              data.ray_direction = "(0, #{dy}, 0)"
              data.expected_xyz = "(#{x}, 0, #{z})"
            end
          end         
        end
      end
    end
  end
end

test_file 'primitives/plane/xz-plane/xz-plane-uv' do
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
        TEST_CASE("[XZ Plane] Local position uv of hits with Ray #{ray_origin} + #{ray_direction} * t", "[XZ Plane]")
        {
            Point3D ray_origin#{ray_origin};
            Vector3D ray_direction#{ray_direction};

            auto primitive = raytracer::primitives::xz_plane();
            Ray ray(ray_origin, ray_direction);

            auto hits = primitive->find_all_hits(ray);

            REQUIRE(hits.size() == 1);
            CHECK(hits[0]->local_position.uv == approx(Point2D#{expected_uv}));
        }
      END
    end

    [-5.7, 0, 9.1].each do |x|
      [-7.7, 0, 2.6].each do |z|
        [-7.1, 1.6, 5.4, 10.1].each do |y|
          [-4.5, 1.0, 2.0].each do |dy|
            test_case do |data|
              data.ray_origin = "(#{x}, #{y}, #{z})"
              data.ray_direction = "(0, #{dy}, 0)"
              data.expected_uv = "(#{x}, #{z})"
            end
          end         
        end
      end
    end
  end
end


test_file 'primitives/plane/yz-plane/yz-plane-t' do
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
        TEST_CASE("[YZ Plane] t-value of hits with Ray #{ray_origin} + #{ray_direction} * t", "[YZ Plane]")
        {
            Point3D ray_origin#{ray_origin};
            Vector3D ray_direction#{ray_direction};

            auto primitive = raytracer::primitives::yz_plane();
            Ray ray(ray_origin, ray_direction);

            auto hits = primitive->find_all_hits(ray);

            REQUIRE(hits.size() == 1);
            CHECK(hits[0]->t == Approx(#{expected_t}));
        }
      END
    end

    [-2, 0, 3.1].each do |z|
      [-2.7, 0, 8.6].each do |y|
        [-7, 1, 5, 10].each do |x|
          [-5.78, 1.0, 2.0, 6.1].each do |dx|
            test_case do |data|
              data.ray_origin = "(#{x}, #{y}, #{z})"
              data.ray_direction = "(#{dx}, 0, 0)"
              data.expected_t = -x / dx
            end
          end         
        end
      end
    end
  end
end

test_file 'primitives/plane/yz-plane/yz-plane-n' do
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
        TEST_CASE("[YZ Plane] Normal of hits with Ray #{ray_origin} + #{ray_direction} * t", "[YZ Plane]")
        {
            Point3D ray_origin#{ray_origin};
            Vector3D ray_direction#{ray_direction};

            auto primitive = raytracer::primitives::yz_plane();
            Ray ray(ray_origin, ray_direction);

            auto hits = primitive->find_all_hits(ray);

            REQUIRE(hits.size() == 1);
            CHECK(hits[0]->normal == approx(Vector3D#{expected_normal}));
        }
      END
    end

    [-2, 0, 2].each do |z|
      [-2, 0, 2].each do |y|
        [1, 5, 10].each do |x|
          [-4.5, 1.0, 2.0].each do |dx|
            test_case do |data|
              data.ray_origin = "(#{x}, #{y}, #{z})"
              data.ray_direction = "(#{dx}, 0, 0)"
              data.expected_normal = "(1, 0, 0)"
            end

            test_case do |data|
              data.ray_origin = "(-#{x}, #{y}, #{z})"
              data.ray_direction = "(#{dx}, 0, 0)"
              data.expected_normal = "(-1, 0, 0)"
            end
          end         
        end
      end
    end
  end
end

test_file 'primitives/plane/yz-plane/yz-plane-position' do
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
        TEST_CASE("[YZ Plane] Position of hits with Ray #{ray_origin} + #{ray_direction} * t", "[YZ Plane]")
        {
            Point3D ray_origin#{ray_origin};
            Vector3D ray_direction#{ray_direction};

            auto primitive = raytracer::primitives::yz_plane();
            Ray ray(ray_origin, ray_direction);

            auto hits = primitive->find_all_hits(ray);

            REQUIRE(hits.size() == 1);
            CHECK(hits[0]->position == approx(Point3D#{expected_position}));
        }
      END
    end

    [-5.7, 0, 9.1].each do |z|
      [-7.7, 0, 2.6].each do |y|
        [-7.1, 1.6, 5.4, 10.1].each do |x|
          [-4.5, 1.0, 2.0].each do |dx|
            test_case do |data|
              data.ray_origin = "(#{x}, #{y}, #{z})"
              data.ray_direction = "(#{dx}, 0, 0)"
              data.expected_position = "(0, #{y}, #{z})"
            end
          end         
        end
      end
    end
  end
end

test_file 'primitives/plane/yz-plane/yz-plane-xyz' do
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
        TEST_CASE("[YZ Plane] Local position xyz of hits with Ray #{ray_origin} + #{ray_direction} * t", "[YZ Plane]")
        {
            Point3D ray_origin#{ray_origin};
            Vector3D ray_direction#{ray_direction};

            auto primitive = raytracer::primitives::yz_plane();
            Ray ray(ray_origin, ray_direction);

            auto hits = primitive->find_all_hits(ray);

            REQUIRE(hits.size() == 1);
            CHECK(hits[0]->local_position.xyz == approx(Point3D#{expected_xyz}));
        }
      END
    end

    [-5.7, 0, 9.1].each do |z|
      [-7.7, 0, 2.6].each do |y|
        [-7.1, 1.6, 5.4, 10.1].each do |x|
          [-4.5, 1.0, 2.0].each do |dx|
            test_case do |data|
              data.ray_origin = "(#{x}, #{y}, #{z})"
              data.ray_direction = "(#{dx}, 0, 0)"
              data.expected_xyz = "(0, #{y}, #{z})"
            end
          end         
        end
      end
    end
  end
end

test_file 'primitives/plane/yz-plane/yz-plane-uv' do
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
        TEST_CASE("[YZ Plane] Local position uv of hits with Ray #{ray_origin} + #{ray_direction} * t", "[YZ Plane]")
        {
            Point3D ray_origin#{ray_origin};
            Vector3D ray_direction#{ray_direction};

            auto primitive = raytracer::primitives::yz_plane();
            Ray ray(ray_origin, ray_direction);

            auto hits = primitive->find_all_hits(ray);

            REQUIRE(hits.size() == 1);
            CHECK(hits[0]->local_position.uv == approx(Point2D#{expected_uv}));
        }
      END
    end

    [-5.7, 0, 9.1].each do |z|
      [-7.7, 0, 2.6].each do |y|
        [-7.1, 1.6, 5.4, 10.1].each do |x|
          [-4.5, 1.0, 2.0].each do |dx|
            test_case do |data|
              data.ray_origin = "(#{x}, #{y}, #{z})"
              data.ray_direction = "(#{dx}, 0, 0)"
              data.expected_uv = "(#{y}, #{z})"
            end
          end         
        end
      end
    end
  end
end
