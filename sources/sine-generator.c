#include <sine-generator.h>

#include <clic3_char_arrays.h>

#include <math_c_circles.h>

#include <stdio.h>

int main(
  int length_parameters,
  char** parameters
) {
  float amplitude = 1;
  float precision = 100;

  unsigned int length_waves = 2;

  unsigned char status_conversion;

  if (
    length_parameters > 1
  ) {
    status_conversion = (
      clic3_char_array_to_float(
        parameters[
          1
        ],
        &amplitude
      )
    );

    if (
      status_conversion != 0
    ) {
      fprintf(
        stderr,
        "invalid_amplitude->{%s};\n",
        parameters[
          1
        ]
      );

      return (
        1
      );
    }
  }

  if (
    length_parameters > 2
  ) {
    status_conversion = (
      clic3_char_array_to_float(
        parameters[
          2
        ],
        &precision
      )
    );

    if (
      status_conversion != 0
    ) {
      fprintf(
        stderr,
        "invalid_precision->{%s};\n",
        parameters[
          2
        ]
      );

      return (
        1
      );
    }
  }

  if (
    length_parameters > 3
  ) {
    status_conversion = (
      clic3_char_array_to_unsigned_int(
        parameters[
          3
        ],
        &length_waves
      )
    );

    if (
      status_conversion != 0
    ) {
      fprintf(
        stderr,
        "invalid_length_waves->{%s};\n",
        parameters[
          3
        ]
      );

      return (
        1
      );
    }
  }

  float amplitude_increment = (
    amplitude /
    precision *
    2.0f
  );

  for (
    unsigned int index_wave = 0;
    index_wave < length_waves;
    ++index_wave
  ) {
    unsigned char inversion = (
      index_wave %
      2
    );

    for (
      float index_y = -amplitude;
      index_y <= amplitude;
      index_y += amplitude_increment
    ) {
      float value_y = (
        math_c_circle_point_y_get(
          index_y,
          amplitude
        )
      );

      if (
        inversion == 1
      ) {
        printf(
          "%f\n",
          -value_y
        );
      } else {
        printf(
          "%f\n",
          value_y
        );
      }
    }
  }

  return (
    0
  );
}
