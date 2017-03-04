.PHONY: clean All

All:
	@echo "----------Building project:[ kek-engine-v2 - Debug ]----------"
	@"$(MAKE)" -f  "kek-engine-v2.mk"
clean:
	@echo "----------Cleaning project:[ kek-engine-v2 - Debug ]----------"
	@"$(MAKE)" -f  "kek-engine-v2.mk" clean
