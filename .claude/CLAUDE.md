# CLAUDE.md

这是一个用于学习光线追踪的c++项目

## 启动流程

写代码之前：

1. **确认工作目录** — 执行 `pwd`
2. **完整阅读本文件**
3. **阅读项目文档**（如有）— `README.md`、`docs/` 目录
4. **执行 `.claude/init.sh`** — 验证环境是否正常
5. **阅读 `.claude/feature_list.json`** — 了解当前特性状态
6. **查看最近提交** — `git log --oneline -5`

如果基线验证失败，先修复再开始新工作。

## 工作规则

- **一次只做一个特性**：从 `.claude/feature_list.json` 中选择一个未完成的特性
- **必须验证**：未通过验证命令之前，不得声称完成
- **更新产物**：会话结束前，更新 `.claude/progress.md` 和 `.claude/feature_list.json`
- **不越界**：不要修改与当前特性无关的文件
- **保持干净**：下个会话必须能直接执行 `.claude/init.sh`
- **事后总结**： 每次会话执行完后，需要向用户汇报“做了什么“，“改动了什么“

## 必需产物

- `.claude/feature_list.json` — 特性状态追踪（事实来源）
- `.claude/progress.md` — 会话进度日志
- `.claude/init.sh` — 标准启动与验证脚本
- `.claude/session-handoff.md` — 可选，多会话交接用

## 完成定义

一个特性只有在以下全部满足时才视为完成：

- [ ] 目标行为已实现，并编写对应的单元测试
- [ ] 要求的验证已实际执行（编译 / 运行 / 测试）
- [ ] 验证证据已记录在 `.claude/feature_list.json` 或 `.claude/progress.md` 中
- [ ] 仓库保持可重启状态（`.claude/init.sh` 能正常运行）

## 会话结束

结束会话前：

1. 更新 `.claude/progress.md` 记录当前状态
2. 更新 `.claude/feature_list.json` 标记特性状态
3. 记录未解决的风险或阻塞项
4. 确保仓库干净，下个会话能直接执行 `.claude/init.sh`

## 验证命令

```bash
# 完整验证（推荐）
.claude/init.sh
```

具体检查项：
- `mkdir -p build && cd build && cmake .. -DCMAKE_BUILD_TYPE=Release && cmake --build . && ./../bin/ray_tracer`

## 升级处理

遇到以下情况时：

- **架构决策**：查阅项目架构文档（如有），否则询问用户
- **需求不明确**：查阅产品/需求文档（如有），否则询问用户
- **重复失败**：更新 .claude/progress.md，标记需要人工介入
- **范围模糊**：重新阅读 `.claude/feature_list.json` 中的完成定义
