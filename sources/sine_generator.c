#include <sine_generator.h>

#include <clic3_char_arrays.h>

#include <math_c_circles.h>

#include <stdio.h>

int main(
  int length_parameters,
  char** parameters
) {
  float amplitude = (
    0x01
  );

  float precision = (
    0x64
  );

  unsigned int length_waves = (
    0x02
  );

  unsigned char status_conversion;

  if (
    length_parameters >
    0x01
  ) {
    status_conversion = (
      clic3_char_array_to_float(
        parameters[
          0x01
        ],
        &amplitude
      )
    );

    if (
      status_conversion !=
      0x00
    ) {
      fprintf(
        stderr,
        "invalid_amplitude->{%s};\n",
        parameters[
          0x01
        ]
      );

      return (
        0x01
      );
    }
  }

  if (
    length_parameters >
    0x02
  ) {
    status_conversion = (
      clic3_char_array_to_float(
        parameters[
          0x02
        ],
        &precision
      )
    );

    if (
      status_conversion !=
      0x00
    ) {
      fprintf(
        stderr,
        "invalid_precision->{%s};\n",
        parameters[
          0x02
        ]
      );

      return (
        0x01
      );
    }
  }

  if (
    length_parameters >
    0x03
  ) {
    status_conversion = (
      clic3_char_array_to_unsigned_int(
        parameters[
          0x03
        ],
        &length_waves
      )
    );

    if (
      status_conversion !=
      0x00
    ) {
      fprintf(
        stderr,
        "invalid_length_waves->{%s};\n",
        parameters[
          0x03
        ]
      );

      return (
        0x01
      );
    }
  }

  float amplitude_increment = (
    amplitude /
    precision *
    0x02
  );

  for (
    unsigned int index_wave = (
      0x00
    );
    (
      index_wave <
      length_waves
    );
    ++index_wave
  ) {
    unsigned char inversion = (
      index_wave %
      0x02
    );

    for (
      float index_y = -(
        amplitude
      );
      (
        index_y <=
        amplitude
      );
      index_y = (
        index_y +
        amplitude_increment
      )
    ) {
      float value_y = (
        math_c_circle_point_y_get(
          index_y,
          amplitude
        )
      );

      if (
        inversion ==
        0x01
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
    0x00
  );
}
