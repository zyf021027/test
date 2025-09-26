int32_t lv_anim_path_linear(const lv_anim_t *a)
{
    /*Calculate the current step*/
    int32_t step = lv_map(a->act_time, 0, a->time, 0, LV_ANIM_RESOLUTION);

    /*Get the new value which will be proportional to `step`
     *and the `start` and `end` values*/
    int32_t new_value;
    new_value = step * (a->end_value - a->start_value);
    new_value = new_value >> LV_ANIM_RES_SHIFT;
    new_value += a->start_value;

    return new_value;
}

int32_t lv_anim_path_fixed_pixel_per_frame(const lv_anim_t *a)
{
/*定义每帧增加的固定像素数*/
#define PIXELS_PER_FRAME 2

    /*计算总帧数 - 假设动画以30fps运行*/
    int32_t total_frames = (a->time * 30) / 1000; // 将毫秒转换为帧数

    /*计算当前帧数*/
    int32_t current_frame = (a->act_time * 30) / 1000;

    /*计算新值：起始值 + (当前帧数 * 每帧像素数)*/
    int32_t new_value = a->start_value + (current_frame * PIXELS_PER_FRAME);

    /*确保不超过结束值*/
    if (a->start_value < a->end_value)
    {
        if (new_value > a->end_value)
            new_value = a->end_value;
    }
    else
    {
        if (new_value < a->end_value)
            new_value = a->end_value;
    }

    return new_value;
}
