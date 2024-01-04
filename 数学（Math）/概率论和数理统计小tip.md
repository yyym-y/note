# 必备公式

## 假设检验

### 检验 $\mu$ , $\sigma$ 已知

$$
检验参数 : u = \frac{\bar{x} - \mu}{\sigma / \sqrt{n}}
$$

分下面的几种情况 : 
$$
\begin{cases}
	\quad T_0 : \mu \le \mu_0 \quad T_1 : \mu > \mu_0 \quad \quad u \ge u_{\alpha} \\\\
	\quad T_0 : \mu \ge \mu_0 \quad T_1 : \mu < \mu_0 \quad \quad u \le -u_{\alpha} \\\\
	\quad T_0 : \mu = \mu_0 \quad T_1 : \mu \ne \mu_0 \quad \quad |u| \ge u_{\frac{\alpha}{2}}
\end{cases}
$$

### 检验 $\mu$ , $\sigma$ 未知

$$
检验参数 : t = \frac{\bar{x} - \mu}{S / \sqrt{n}}
$$

分下面的几种情况 : 
$$
\begin{cases}
	\quad T_0 : \mu \le \mu_0 \quad T_1 : \mu > \mu_0 \quad \quad t \ge t_{\alpha}(n - 1) \\\\
	\quad T_0 : \mu \ge \mu_0 \quad T_1 : \mu < \mu_0 \quad \quad t \le -t_{\alpha}(n - 1) \\\\
	\quad T_0 : \mu = \mu_0 \quad T_1 : \mu \ne \mu_0 \quad \quad |t| \le t_{\frac{\alpha}{2}}(n - 1)
\end{cases}
$$

### 检验 $\sigma$ , $\mu$ 未知

$$
检验参数 : \chi = \frac{(n - 1)S^2}{\sigma_0 ^2}
$$

分下面的几种情况 : 
$$
\begin{cases}
	\quad T_0 : \sigma \le \sigma_0 \quad T_1 : \sigma > \sigma_0 \quad \quad \chi \ge \chi^2_{\alpha}(n - 1) \\\\
	\quad T_0 : \sigma \ge \sigma_0 \quad T_1 : \sigma < \sigma_0 \quad \quad \chi \le -\chi^2_{1-\alpha}(n - 1) \\\\
	\quad T_0 : \sigma = \sigma_0 \quad T_1 : \sigma \ne \sigma_0 \quad \quad \chi \le \chi^2_{1-\frac{\alpha}{2}}(n - 1) \or \chi \ge \chi^2_{\frac{\alpha}{2}}(n - 1)
\end{cases}
$$
在拒绝域中, 