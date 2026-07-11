# antialiasing

## Purpose

通过多重采样（supersampling）消除渲染图像中的锯齿边缘，每个像素发射多条随机偏移光线取平均值。

## Requirements

### Requirement: 每个像素多次采样取平均
渲染主循环 SHALL 对每个像素发射 `kSamplesPerPixel` 条光线，每条光线的子像素位置加上随机偏移，最终颜色为所有采样颜色的算术平均值。

#### Scenario: 采样数大于 1 时颜色被平均
- **WHEN** `kSamplesPerPixel = 100`，像素颜色为 100 次采样的累加值除以 100
- **THEN** 颜色值在 [0, 1] 范围内

#### Scenario: 颜色使用 glm::clamp 防止溢出
- **WHEN** 平均后的颜色分量超出 [0, 1] 范围
- **THEN** `glm::clamp` 将其钳制到 [0, 1]

### Requirement: 子像素位置随机抖动
每条采样光线 SHALL 在像素区域内使用随机偏移量，而非固定网格位置。偏移量使用 `RandomFloat()` 生成，范围 [0, 1)。

#### Scenario: 两次渲染产生不同采样位置
- **WHEN** 连续两次运行渲染器
- **THEN** 同一像素的采样位置不同（随机种子不同）
