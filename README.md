# 情景1.向你的分支提交代码
```
git add *
git commit -m "你说的话"
git push origin 你的分支名字
```


# 情景2.分支跟主分支做同步
```

git fetch  
git checkout main
git pull
git merge 你的分支名
```
**处理文件冲突(没有最好)有的话小心处理全部选择好保留的内容后**
```
git add *
git commit -m "你说的话"
git push 

git checkout 你的分支
git merge main
```
**(一般不会有任何问题)有问题,,手动小心处理冲突**
```
git add *
git commit  -m "你说的话"
git push 
```
# 3.备注

**应该没问题了吧,注意每个情景都要做完整,顺序不要乱,少做一点都会对整个项目造成不可估量的后果**
