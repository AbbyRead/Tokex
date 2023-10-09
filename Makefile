# Define directory names
src_dir := src
obj_dir := obj
bin_dir := bin

# Leaving CC as default for ease of use

# Define compiler flags
CFLAGS := -Wall -Wextra -I$(src_dir)

# List of source files (all .c files in src/)
src_files := $(wildcard $(src_dir)/*.c)

# Generate object file names from source file names
obj_files := $(patsubst $(src_dir)/%.c,$(obj_dir)/%.o,$(src_files))
.SECONDARY: $(obj_files)

.PHONY: all, clean, cleanio

# Default target
all : $(bin_dir)/convert convert.sh

# Rule to compile .c files into .o files
$(obj_dir)/%.o: $(src_dir)/%.c | $(obj_dir)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to link .o files into binaries
$(bin_dir)/convert: $(obj_files) | $(bin_dir)
	$(CC) $< -o $@

$(obj_dir):
	mkdir -p $(obj_dir)

$(bin_dir):
	mkdir -p $(bin_dir)

input:
	@mkdir -p input

convert.sh: input
	@echo 'input_folder="input"' > convert.sh
	@echo 'output_folder="output"' >> convert.sh
	@echo '' >> convert.sh
	@echo "# Create the output folder if it doesn't exist" >> convert.sh
	@echo 'mkdir -p "$$output_folder"' >> convert.sh
	@echo '' >> convert.sh
	@echo '# Iterate through each file in the input folder' >> convert.sh
	@echo 'for input_file in "$$input_folder"/*; do' >> convert.sh
	@echo '    # Extract the file name without the path and extension' >> convert.sh
	@echo '    filename=$$(basename -- "$$input_file")' >> convert.sh
	@echo '    filename_no_extension="$${filename%.*}"' >> convert.sh
	@echo '' >> convert.sh
	@echo '    # Generate the output file path in the output folder' >> convert.sh
	@echo '    output_file="$$output_folder/$$filename_no_extension.bin"' >> convert.sh
	@echo '' >> convert.sh
	@echo '    # Run your program to process the input file and create the output binary file' >> convert.sh
	@echo '    ./bin/convert "$$input_file" "$$output_file"' >> convert.sh
	@echo '' >> convert.sh
	@echo '    # Optionally, you can add error handling here to check if the program executed successfully.' >> convert.sh
	@echo '    # If not, you can log an error or take appropriate action.' >> convert.sh
	@echo '' >> convert.sh
	@echo '    echo "Processed $$input_file -> $$output_file"' >> convert.sh
	@echo 'done' >> convert.sh
	@echo '' >> convert.sh
	@echo 'echo "Processing complete."' >> convert.sh
	@chmod +x convert.sh

clean:
	rm -rf convert.sh $(obj_dir) $(bin_dir)

cleanio:
	rm -rf input output