import numpy as np
import matplotlib.pyplot as plt

# Parameters
num_samples = 512       # Number of points
amplitude = 4095        # For a 12-bit DAC (0–4095)
frequency = 1           # 1 Hz sine wave
sample_rate = 512       # Samples per second (1 cycle)

# Generate sample points (0 to 2π)
t = np.arange(num_samples)
sine_wave = amplitude * (np.sin(2 * np.pi * frequency * t / sample_rate) + 1) / 2  # 0–4095 range

# Convert to integers (for DAC)
sine_wave_int = np.round(sine_wave).astype(np.uint16)

# --- Save to C array format ---
output_filename = "sine_wave_512.c"

with open(output_filename, "w") as f:
    f.write(f"// {num_samples}-sample sine wave for 12-bit DAC\n")
    f.write(f"uint16_t waveForm[{num_samples}] = {{\n")

    # Write 8 values per line for readability
    for i in range(0, num_samples, 8):
        line = ", ".join(f"{v:5d}" for v in sine_wave_int[i:i+8])
        if i + 8 < num_samples:
            f.write(f"    {line},\n")
        else:
            f.write(f"    {line}\n")

    f.write("};\n")

print(f"\n C array saved to '{output_filename}' successfully!")

# --- Optional: plot it ---
plt.plot(t, sine_wave_int)
plt.title("512-sample Sine Wave (12-bit DAC Range)")
plt.xlabel("Sample index")
plt.ylabel("Amplitude")
plt.grid(True)
plt.show()
