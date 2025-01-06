#include <stdio.h>
#include "../include/minirt.h"

void print_vec(t_vec vec) {
    printf("Vector: (x: %.2f, y: %.2f, z: %.2f)\n", vec.x, vec.y, vec.z);
}

void print_ambient(t_amb amb) {
    printf("Ambient: (ratio: %.2f, color: %d)\n", amb.ratio, amb.color);
}

void print_camera(t_cam cam) {
    printf("Camera position:\n");
    print_vec(cam.pos);
    printf("Camera orientation:\n");
    print_vec(cam.ori);
    printf("Camera FOV: %.2f\n", cam.fov);
}

void print_light(t_light light) {
    printf("Light position:\n");
    print_vec(light.pos);
    printf("Light ratio: %.2f\n", light.ratio);
    printf("Light color: %d\n", light.color);
}

void print_sphere(t_sphere sphere) {
    printf("Sphere center:\n");
    print_vec(sphere.center);
    printf("Sphere radius: %.2f\n", sphere.radius);
}

void print_scene(t_scene scene) {
    printf("Scene:\n");
    
    printf("Objects count: %d\n", scene.objc);
    for (int i = 0; i < scene.objc; i++) {
        // Assuming all objects are spheres for simplicity
        // You should add checks and print functions for other object types
        printf("Object %d:\n", i + 1);
        print_sphere(*(t_sphere *)(scene.objs[i].self));
        printf("Object color: %d\n", scene.objs[i].color);
    }
    
    print_light(scene.light);
    print_ambient(scene.amb);
    print_camera(scene.cam);
}

void write_int_bytes(int value) {
    unsigned char *byte_ptr = (unsigned char *)&value;
    for (int i = 0; i < 4; i++) {
        printf("Byte %d: %02X\n", i, byte_ptr[i]);
    }
}
